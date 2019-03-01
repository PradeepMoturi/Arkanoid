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
#include "powerup.h"
#include <QBrush>
#include <QDebug>
Powerup::Powerup(QGraphicsItem *parent):QGraphicsRectItem (parent)
{
    x_velocity = 0;
    y_velocity = 1;
    powerup_width=50;
    powerup_height=8;
    setRect(0,0,powerup_width,powerup_height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
};
void Powerup::set(int id,double x, double y)
{
    powerup_id = id;
    setPos(x,y);
}

void Powerup::powerup_move()
{
    qreal temp = 700;

    setPos(x(),y()+y_velocity);
    if (y()> temp)
    {
        emit remove_connection(this);
    }
}
double Powerup::getwidth()
{
    return powerup_width;
}

double Powerup::getheight()
{
    return powerup_height;
}
