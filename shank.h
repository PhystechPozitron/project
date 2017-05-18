#ifndef SHANK_H
#define SHANK_H

#include <spring.h>

class Shank: public Spring
{
    Q_OBJECT

public:
    explicit Shank(Spring* parent = 0);
    ~Shank();
private:
    QPainter* painter;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SHANK_H
