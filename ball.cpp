#include "ball.h"
#include "game.h"
#include "paddle.h"
#include "brick.h"
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include <QtMath>
extern Game* game;

Ball::Ball(QGraphicsItem *parent):QGraphicsEllipseItem(parent){
    ball_radius=20;
    x_velocity = -1;
    y_velocity = -2;
    setRect(0,0,ball_radius,ball_radius);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    setPos(game->width()/2-this->radius()/2,game->height()-30-this->radius());
}

double Ball::radius(){return ball_radius;}
double Ball::getCenterX(){return x() + rect().width()/2;}
double Ball::get_xvelocity(){return x_velocity;}
double Ball::get_yvelocity(){return y_velocity;}

void Ball::set_xvelocity(bool pos)
{
    mutex.lock();
    if(pos)x_velocity=abs(x_velocity);
    else x_velocity=-1*abs(x_velocity);
    mutex.unlock();
}
void Ball::set_yvelocity(bool pos)
{
    mutex.lock();
    if(pos)y_velocity=abs(y_velocity);
    else y_velocity=-1*abs(y_velocity);
    mutex.unlock();
}
