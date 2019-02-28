/*
Copyright (c) 2019 Revanth Babu, Pradeep Moturi, Jeevan Chandra, Udit Maniyar

This file is part of Arkanoid 
(see https://github.com/IITH-SBJoshi/concurrency-1).

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
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
