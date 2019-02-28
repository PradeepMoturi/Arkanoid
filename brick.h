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
#ifndef GRID_H
#define GRID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

class Brick:public QGraphicsItem
{
public:
    Brick(int id,int cnt,QGraphicsItem *parent=nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getHits();
    int getHeight();
    int getWidth();
    void decHits();
    void setHeight(int x);
    void setWidth(int x);
    int brick_id;

private:
    int hits;
    int height;
    int width;
};

#endif // GRID_H
