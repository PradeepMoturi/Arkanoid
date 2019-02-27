#include "brick.h"
#include <QBrush>
#include <QPainter>

Brick::Brick(int id,int cnt,QGraphicsItem* parent):QGraphicsItem(parent)
{
    brick_id=id;
    hits=cnt;
    width=80;
    height=20;
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
    return QRectF(0,0,width,height);
}


int Brick::getHeight(){return height;}
int Brick::getWidth(){return width;}
void Brick::setHits(int temp){this->hits=temp;}
void Brick::setHeight(int temp){this->height=temp;}
void Brick::setWidth(int temp){this->width=temp;}
