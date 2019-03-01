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

Ball::Ball(QGraphicsItem *parent):QGraphicsEllipseItem(parent)
{
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

double Ball::radius()
{
    return ball_radius;
}

double Ball::getCenterX()
{
    return x() + rect().width()/2;
}

double Ball::get_xvelocity()
{
    return x_velocity;
}

double Ball::get_yvelocity()
{
    return y_velocity;
}

void Ball::set_xvelocity(bool pos)
{
    mutex.lock();

    if(pos)
    {
        x_velocity=abs(x_velocity);
    }
    else
    {
        x_velocity=-1*abs(x_velocity);
    }

    mutex.unlock();
}
void Ball::set_yvelocity(bool pos)
{
    mutex.lock();

    if(pos)
    {
        y_velocity=abs(y_velocity);
    }

    else
    {
        y_velocity=-1*abs(y_velocity);
    }
    mutex.unlock();
}
