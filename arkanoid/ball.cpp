#include "ball.h"
#include "game.h"
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

extern Game* game;

Ball::Ball(QGraphicsItem *parent):QGraphicsEllipseItem(parent){
    ball_radius=20;
    setRect(0,0,ball_radius,ball_radius);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}

double Ball::radius()
{
    return ball_radius;
}

void Ball::move()
{
    if(x()<=700)
    {
        setPos(x()+10,y());
    }

    else if(y()>=0)
    {
        setPos(x(),y()-10);
    }
}
