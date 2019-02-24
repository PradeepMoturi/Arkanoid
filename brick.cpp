#include "brick.h"
#include <QBrush>
#include <QPainter>

Brick::Brick(int cnt,QGraphicsItem* parent):QGraphicsItem(parent)
{
    hits=cnt;
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF map=boundingRect();
    if(hits==1) painter->setBrush(Qt::yellow);
    else painter->setBrush(Qt::red);
    painter->drawRoundedRect(map,4,4);
}

QRectF Brick::boundingRect() const
{
    return QRectF(0,0,80,20);
}
