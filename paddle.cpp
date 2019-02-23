#include "paddle.h"
#include "game.h"
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include <QtGlobal>
extern Game* game;

Paddle::Paddle(QGraphicsItem *parent):QGraphicsRectItem (parent)
{
    std::cout<<"Working";
    paddle_width=100;
    paddle_height=20;
    //this->width() = 20;
    setRect(0,0,paddle_width,paddle_height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
    setPos(game->width()/2-this->width()/2,game->height()-30);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    startTimer(1000/60);
};

void Paddle::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
}
void Paddle::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] =false;
}
void Paddle::timerEvent(QTimerEvent *)
{
    if(keys[Qt::Key_Left]==true)
    {
          move_paddle(-5);
    }

    if(keys[Qt::Key_Right]==true)
    {
          move_paddle(5);
    }
}

void Paddle::move_paddle(double dis)
{
    double slide=x()+dis;

    if(slide>=game->width()-this->width())
    {
        slide=game->width()-this->width();
    }

    else if(slide<=0)
    {
        slide=0;
    }

    this->setPos(slide,y());
}
void Paddle::CollisionChecker(qreal x, qreal y, double radius)
{
    QGraphicsEllipseItem* copy = new QGraphicsEllipseItem();
    copy->setRect(0,0,radius,radius);
    copy->setPos(x,y);

    QGraphicsRectItem* right = new QGraphicsRectItem();
    right->setRect(0,0,1,this->height());
    right->setPos(this->x()+this->width(),this->y());

    QGraphicsRectItem* left = new QGraphicsRectItem();
    left->setRect(0,0,1,this->height());
    left->setPos(this->x(),this->y());


    qDebug()<<this->x()+this->width()<<" "<<this->y()+this->height()<<" "<<this->x()+this->width()<<" "<<this->y();

    bool chk = copy->collidesWithItem(this);
    bool right_collision = right->collidesWithItem(this);
    bool left_collision = left->collidesWithItem(this);
    if(chk==true)
    {
        if(keys[Qt::Key_Left]==true)
        {
            emit ballCollision(-1,left_collision,right_collision);
        }
        else if(keys[Qt::Key_Right]==true)
        {
            emit ballCollision(1,left_collision,right_collision);
        }
        else
        {
            emit ballCollision(0,left_collision,right_collision);
        }
    }
}
qreal Paddle::width()
{
    return paddle_width;
}

qreal Paddle::height()
{
    return paddle_height;
}

