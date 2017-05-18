#ifndef SPRING_H
#define SPRING_H

#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <windows.h>

class Spring: public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Spring(QGraphicsObject *parent = 0);
    ~Spring();
    void setPosEnd(double cx,double cy);
    double getForce();
    double getForceX(QGraphicsObject *pointer);
    double getForceY(QGraphicsObject *pointer);
    void addCircle(QGraphicsObject *pointer, bool begin); // добавление шарика к пружине
    QGraphicsObject *circleBegin;
    double xEnd = 0,yEnd = 0; // координаты шарика, соединенного с пружиной

    /* характеристики пружины */
    void setRate(double input_Rate);
    double getRate();
    void setLength0();

private:
    double c,r0; // параметры пружины
    int N; // число зигзагов
    QRectF boundingRect() const;
    QPainter *painter;
    double getLength();
    double getAngle();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SPRING_H
