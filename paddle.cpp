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
#include "paddle.h"
#include "game.h"
#include "ball.h"
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include <QtGlobal>
#include "powerup.h"
extern Game* game;

Paddle::Paddle(QGraphicsItem *parent):QGraphicsRectItem (parent)
{
    paddle_width=100;
    paddle_height=20;
    cnt = 0;
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
    if(event->key()==Qt::Key_Escape)
    {
        emit stop();
    }
    else
    {
        keys[event->key()] = true;
    }
}
void Paddle::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] =false;
}
void Paddle::timerEvent(QTimerEvent *)
{
    if(keys[Qt::Key_Left]==true)
    {
          move_paddle(-10);
    }

    if(keys[Qt::Key_Right]==true)
    {
          move_paddle(10);
    }
    CollisionChecker();
    if(cnt>0)
    {
        cnt++;
        if(cnt>600)
        {
            cnt = 0;
            if(paddle_width>101)
            {
                paddle_width = 100;
                this->setRect(25,0,paddle_width,paddle_height);
//              this->move_paddle(25);
            }
            if(paddle_width<99)
            {
                paddle_width = 100;
                this->setRect(-25,0,paddle_width,paddle_height);
//              this->move_paddle(-25);
            }
        }
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
void Paddle::CollisionChecker()
{
    QList<QGraphicsItem*> cItems = collidingItems();
    for (int i = 0, n = cItems.size(); i < n; ++i)
    {
         Ball* object = dynamic_cast<Ball*>(cItems[i]);
         if (object)
         {
             if(object->getCenterX()>=this->leftCornerX()&&object->getCenterX()<=this->rightCornerX()&&object->y()+(object->rect().width()/2)<y())
             {
                emit ballCollision(dynamic_cast<Ball*>(cItems[i]),false,false);
                return;
             }
             else if(object->getCenterX()>=this->leftCornerX())
             {
                 emit ballCollision(dynamic_cast<Ball*>(cItems[i]),false,true);
             }
             else
             {
                 emit ballCollision(dynamic_cast<Ball*>(cItems[i]),true,false);
             }
         }

        Powerup* power = dynamic_cast<Powerup*>(cItems[i]);
        if(power)
        {
            if(power->powerup_id==1)
            {
                emit multiballadd();
            }
            if(power->powerup_id == 2)
            {
                cnt = 1;
                paddle_width = 150;
                this->setRect(-25,0,paddle_width,paddle_height);
//                this->move_paddle(-25);
            }
            if(power->powerup_id == 3)
            {
                cnt = 1;
                paddle_width = 50;
                this->setRect(25,0,paddle_width,paddle_height);
//                this->move_paddle(25);
            }
            if(power->powerup_id==4)
            {
                emit(sendStatus());
            }
            emit destroy_powerup(power);
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
double Paddle::getCenterX(){
    return x()+(rect().width()/2);
}
double Paddle::rightCornerX()
{
    return x()+rect().width();
}
double Paddle::leftCornerX()
{
    return x();
}
