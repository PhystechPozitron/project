#include "circle.h"
#include <iostream>
#include "const.h"

//* конструктор и деструктор класса *//

Circle::Circle(QGraphicsObject *parent):
    QGraphicsObject(parent)
{

}

Circle::~Circle()
{

}

//* графические методы *//

QRectF Circle::boundingRect() const
{
    return QRectF(-2*r,-2*r,4*r,4*r);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(QPointF(0,0),this->r,this->r);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//* методы задания и возвращения параметров шарика *//

void Circle::setVx(double Vx)
{
    vx = Vx;
}

double Circle::getVx()
{
    return vx;
}

void Circle::setVy(double Vy)
{
    vy = Vy;
}

double Circle::getVy()
{
    return vy;
}

void Circle::setMass(double Mass)
{
    m = Mass;
}

double Circle::getMass()
{
    return m;
}

void Circle::setRadius(double Radius)
{
    r = Radius;
}

double Circle::getRadius()
{
    return r;
}

void Circle::setDissipation(double Dissipation)
{
    diss = Dissipation;
}

//* динамические методы *//

double Circle::getSpeed()
{
    return sqrt(pow(vx,2) + pow(vy,2));
}

void Circle::calcAcceleration()
{
    double Fx = 0,Fy = 0;

    /* рассчитываем силы, действующие со стороны пружин */
    for(unsigned int i = 0;i < this->attachedSprings.size();i++ ) {
        Fx += this->attachedSprings[i]->getForceX(this);
        Fy += this->attachedSprings[i]->getForceY(this);
    };
    /* рассчитываем силы, действующие со стороны стержней */
    for(unsigned int i = 0;i < this->attachedShanks.size();i++ ) {
        Fx += this->attachedShanks[i]->getForceX(this);
        Fy += this->attachedShanks[i]->getForceY(this);
    };

    /* переводим силы в ускорения */
    if (this->getSpeed() <= 3) {
        wx = Fx/m - diss*vx;
        wy = Fy/m + g - diss*vy;
    } else {
        wx = Fx/m - diss*vx*this->getSpeed();
        wy = Fy/m + g - diss*vy*this->getSpeed();
    }
}

void Circle::wallCollision()
{
    if ((this->y() + r) >= sizeViewY) {
        wy += wall_rate*(-this->y() - r + sizeViewY)/m;
    }
    if (this->y() <= r) {
        wy += wall_rate*(-this->y() + r)/m;
    }
    if ((this->x() + r) >= sizeViewX) {
        wx += wall_rate*(-this->x() - r + sizeViewX)/m;
    }
    if (this->x() <= r) {
        wx += wall_rate*(-this->x() + r)/m;
    }
}

double Circle::distanceFrom(Circle* other)
{
    return sqrt(pow(other->x() - this->x(),2) + pow(other->y() - this->y(),2));
}

void Circle::interaction(Circle* other)
{
    if (this->distanceFrom(other) <= r + other->getRadius()) {
        double F = -circle_rate*(r - other->getRadius() + this->distanceFrom(other)); // модуль силы отталкивания
        double Fx = F*(other->x() - this->x())/this->distanceFrom(other);
        double Fy = F*(other->y() - this->y())/this->distanceFrom(other); // проекции на оси координат
        wx += Fx/m;
        wy += Fy/m;
    }
}

void Circle::move()
{
    /* кинематика */

    vx += wx;
    vy += wy;
    this->setX(this->x() + vx);
    this->setY(this->y() + vy);

    /* движение пружин */
    for(unsigned int i = 0;i < this->attachedSprings.size();i++ ) {
        if (this == this->attachedSprings[i]->circleBegin) {
            this->attachedSprings[i]->setPos(this->x(),this->y());
        } else {
            this->attachedSprings[i]->setPosEnd(this->x(),this->y());
        };
    };

    /* движение стержней */
    for(unsigned int i = 0;i < this->attachedShanks.size();i++ ) {
        if (this == this->attachedShanks[i]->circleBegin) {
            this->attachedShanks[i]->setPos(this->x(),this->y());
        } else {
            this->attachedShanks[i]->setPosEnd(this->x(),this->y());
        };
    };
}
