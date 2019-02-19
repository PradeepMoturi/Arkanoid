#include "paddle.h"
#include "game.h"
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>

extern Game* game;

Paddle::Paddle(QGraphicsItem *parent):QGraphicsRectItem (parent)
{
    paddle_width=100;
    paddle_height=20;

    setRect(0,0,paddle_width,paddle_height);
    QBrush brush;

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
};

void Paddle::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left)
    {
        this->move_paddle(-30);
    }

    else if(event->key()==Qt::Key_Right)
    {
        this->move_paddle(30);
    }

    else if(event->key()==Qt::Key_Q)
    {
        qDebug()<<"Quit key was pressed";
        emit stop_game();
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

double Paddle::width()
{
    return paddle_width;
}

double Paddle::height()
{
    return paddle_height;
}

