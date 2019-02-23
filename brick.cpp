#include "brick.h"
#include <QBrush>
#include <QPainter>

Brick::Brick(QGraphicsItem* parent):QGraphicsItem(parent)
{}
void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF map=boundingRect();
    painter->setBrush(Qt::yellow);
    painter->drawRoundedRect(map,4,4);
}

QRectF Brick::boundingRect() const
{
    return QRectF(0,0,80,20);
}
