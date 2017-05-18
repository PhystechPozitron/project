#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <spring.h>
#include <shank.h>
#include <windows.h>
#include <vector>

class Circle : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Circle(QGraphicsObject *parent = 0);
    std::vector <Spring*> attachedSprings;
    std::vector <Shank*> attachedShanks;
    ~Circle();

    void calcAcceleration(); // расчет ускорений шариков
    void wallCollision(); // обработка столкновений со стенками
    void interaction(Circle* other); // обработка взаимодействий с другими шариками
    void move(); // кинематика шариков

    /* характеристики шарика */
    void setVx(double Vx);
    double getVx();
    void setVy(double Vy);
    double getVy();
    void setMass(double Mass);
    double getMass();
    void setRadius(double Radius);
    double getRadius();
    void setDissipation(double Dissipation);

private:
    double vx = 0,vy = 0; // скорость
    double wx = 0,wy = 0; // ускорение
    double r,m; // радиус и масса
    double diss; // фактор диссипации
    double getSpeed();
    double distanceFrom(Circle* other);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool intoScene();

};
#endif // CIRCLE_H
