#include "spring.h"
#include "math.h"
#include <iostream>

static const double Pi = 3.1415;

// конструктор и деструктор класса *//

Spring::Spring(QGraphicsObject *parent):
    QGraphicsObject(parent)
{
    N = 15;
}

Spring::~Spring()
{

}

//* графические методы *//

QRectF Spring::boundingRect() const
{
    double width = 2*sqrt(pow(xEnd - this->x(),2) + pow(yEnd - this->y(),2));
    return QRectF(-width/2,-width/2,width,width);
}

void Spring::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    painter->setPen(pen);

    /* рисуем пружину с числом зигзагов N */

    double b = (this->getLength() - 40)/(2*N + 1); // длина цепочки
    double p0 = atan(2*(r0 - 40)/(b*(2*N + 1))); // угол зигзага
    double a = 0.5*b/cos(p0); // сторона треугольника
    QPainterPath path;
    QPointF next;
    path.moveTo(0,0);
    next.setX(20*cos(this->getAngle()));
    next.setY(20*sin(this->getAngle()));
    path.lineTo(next);
    next.setX(next.x() + a*cos(p0 - this->getAngle()));
    next.setY(next.y() - a*sin(p0 - this->getAngle()));
    path.lineTo(next);
    for(int i = 0; i < N; i++) {
        next.setX(next.x() - 2*a*cos(Pi - p0 - this->getAngle()));
        next.setY(next.y() + 2*a*sin(Pi - p0 - this->getAngle()));
        path.lineTo(next);
        next.setX(next.x() + 2*a*cos(p0 - this->getAngle()));
        next.setY(next.y() - 2*a*sin(p0 - this->getAngle()));
        path.lineTo(next);
    }
    next.setX(next.x() - a*cos(Pi - p0 - this->getAngle()));
    next.setY(next.y() + a*sin(Pi - p0 -  this->getAngle()));
    path.lineTo(next);
    next.setX(next.x() + 20*cos(this->getAngle()));
    next.setY(next.y() + 20*sin(this->getAngle()));
    path.lineTo(next);

    painter->drawPath(path);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//* методы задания и возвращения параметров пружины *//

void Spring::setRate(double input_Rate)
{
    c = input_Rate;
}

double Spring::getRate()
{
    return c;
}

void Spring::setLength0()
{
    r0 = this->getLength();
}

//* динамические методы *//

void Spring::setPosEnd(double cx,double cy)
{
    this->prepareGeometryChange();
    xEnd = cx;
    yEnd = cy;
}

double Spring::getLength()
{
    return sqrt(pow(xEnd - this->x(),2) + pow(yEnd - this->y(),2));
}

double Spring::getForce()
{
    return c*(r0 - this->getLength());
}

double Spring::getForceX(QGraphicsObject* pointer)
{
    double F,Fx;
    F = this->getForce();
    Fx = F*(xEnd - this->x())/this->getLength();
    if (pointer == circleBegin) Fx = -Fx;
    return Fx;
}

double Spring::getForceY(QGraphicsObject* pointer)
{
    double F,Fy;
    F = this->getForce();
    Fy = F*(yEnd - this->y())/this->getLength();
    if (pointer == circleBegin) Fy = -Fy;
    return Fy;
}

double Spring::getAngle()
{
    double dx = xEnd - this->x();
    double dy = yEnd - this->y();
    double angle = 0;
    if ((dy >= 0)&&(dx > 0)) angle = atan(dy/dx);
    if ((dx == 0)&&(dy > 0)) angle = Pi/2;
    if (dx < 0) angle = Pi + atan(dy/dx);
    if ((dx == 0)&&(dy < 0)) angle =  3*Pi/2;
    if ((dy < 0)&&(dx > 0)) angle = 2*Pi + atan(dy/dx);
    return angle;
}

void Spring::addCircle(QGraphicsObject *pointer, bool begin)
{
    if (begin) {
        circleBegin = pointer;
        this->setPos(pointer->x(),pointer->y());
    } else {
        this->setPosEnd(pointer->x(),pointer->y());
    }
}
