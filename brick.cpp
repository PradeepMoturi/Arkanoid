#include "brick.h"
#include <QBrush>
#include <QPainter>
#include <QMutex>

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
    if(this->getHits()==1) painter->setBrush(Qt::yellow);
    else painter->setBrush(Qt::red);
    painter->drawRoundedRect(map,4,4);
}

QRectF Brick::boundingRect() const
{
    return QRectF(0,0,width,height);
}

int Brick::getHits()
{
    return hits;
}
void Brick::decHits()
{
    QMutex mutex;
    mutex.lock();
    hits=hits-1;
    mutex.unlock();
}
int Brick::getHeight(){return height;}
int Brick::getWidth(){return width;}
void Brick::setHeight(int temp){this->height=temp;}
void Brick::setWidth(int temp){this->width=temp;}
