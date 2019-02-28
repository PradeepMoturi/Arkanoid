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

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QRectF map=boundingRect();
    if(this->getHits()==1)
    {
        painter->setBrush(Qt::yellow);
    }
    else
    {
        painter->setBrush(Qt::red);
    }
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
    hits=hits-1;
}

int Brick::getHeight()
{
    return height;
}

int Brick::getWidth()
{
    return width;
}

void Brick::setHeight(int new_height)
{
    this->height=new_height;
}

void Brick::setWidth(int new_width)
{
    this->width=new_width;
}
