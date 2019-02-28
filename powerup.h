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
#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class Powerup:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    Powerup(QGraphicsItem* parent = nullptr);
    void set(int id, double x, double y);
    int powerup_id;
    double getwidth();
    double getheight();
private:
    double x_velocity;
    double y_velocity;
    double powerup_width;
    double powerup_height;
signals:
    void remove_connection(Powerup*);
public slots:
    void powerup_move();
};

#endif // POWERUP_H
