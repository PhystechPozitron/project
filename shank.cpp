#include <shank.h>
#include <const.h>

Shank::Shank(Spring *parent):
    Spring(parent)
{
    this->setRate(shank_rate);
}

Shank::~Shank()
{

}

void Shank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::black);
    painter->setPen(pen);

    painter->drawLine(0,0,xEnd - this->x(),yEnd - this->y());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
