#include <QDebug>
#include <math.h>
#include <QtMath>
#include "ballworker.h"
#include "brick.h"

ballworker::ballworker(QGraphicsScene* curr,Ball* b)
{
    screen_width = curr->width();
    screen_height = curr->height();
    ball = b;
    screen_width = 700;
    screen_height = 700;
}

ballworker ::~ballworker(){}

void ballworker::ball_move()
{
    wall_collision();
    emit(ballposupdater(ball,ball->x()+ball->get_xvelocity(),ball->y()+ball->get_yvelocity()));
}

void ballworker::PaddleCollisionDetected(Ball* nball,bool left_corner,bool right_corner)
{
       if(left_corner == false&&right_corner==false)
       {
           nball->set_yvelocity(false);
       }
       else if(left_corner==true)
       {
           nball->set_xvelocity(false);
       }
       else
       {
           nball->set_xvelocity(true);
       }
}

void ballworker::wall_collision()
{
    if (ball->mapToScene(ball->rect().topLeft()).x() <= 0)
    {
        ball->set_xvelocity(true);
    }

    if (ball->mapToScene(ball->rect().topRight()).x() >= screen_width)
    {
        ball->set_xvelocity(false);
    }

    if (ball->mapToScene(ball->rect().topLeft()).y()<= 0)
    {
        ball->set_yvelocity(true);
    }

    if (ball->mapToScene(ball->rect().topRight()).y()> screen_height)
    {
        emit(endgame(this,ball));
        return;
    }
}
