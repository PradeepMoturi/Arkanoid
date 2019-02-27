#include <QDebug>
#include <QtMath>
#include "ballworker.h"
#include "brick.h"

ballworker::ballworker(QGraphicsScene* curr,Ball* b)
{
    screen_width = curr->width();
    screen_height = curr->height();
    scene = curr;
    ball = b;
    screen_width = 700;
    screen_height = 700;
}
ballworker ::~ballworker()
{

}

void ballworker::ball_move()
{
    wall_collision();

    emit(ballposupdater(ball,ball->x()+ball->x_velocity,ball->y()+ball->y_velocity));
}

void ballworker::PaddleCollisionDetected(Ball* nball,bool left_corner,bool right_corner)
{
       if(left_corner == false&&right_corner==false)
       {
           nball->y_velocity = -abs(ball->y_velocity);
       }
       else if(left_corner==true)
       {
           nball->x_velocity = -abs(ball->x_velocity);
       }
       else
       {
           nball->x_velocity = abs(ball->x_velocity);
       }
}

void ballworker::wall_collision()
{

    // left edge
    if (ball->mapToScene(ball->rect().topLeft()).x() <= 0)
    {
        ball->x_velocity = -1 * ball->x_velocity;
    }

    // right edge
    if (ball->mapToScene(ball->rect().topRight()).x() >= screen_width)
    {
        ball->x_velocity = -1 * ball->x_velocity;
    }

    // top edge
    if (ball->mapToScene(ball->rect().topLeft()).y()<= 0)
    {
        ball->y_velocity = -1 * ball->y_velocity;
    }

    //bottom edge
    if (ball->mapToScene(ball->rect().topRight()).y()> screen_height)
    {
        emit(endgame(scene,ball));
        return;
    }
}
