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
#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QObject>
#include "ball.h"
#include"powerup.h"

class Paddle:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    Paddle(QGraphicsItem *parent=nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent* event);
    void move_paddle(double x);
    qreal height();
    qreal width();
    double getCenterX();
    double rightCornerX();
    double leftCornerX();
    void timerEvent(QTimerEvent *);
    void CollisionChecker();
signals:
    void multiballadd();
    void destroy_powerup(Powerup *);
    void stop();
    void stop_game();
    void ballCollision(Ball* ball,bool left_corner,bool right_corner);
private:
    int cnt = 0;
    bool foo = true;
    double paddle_height;
    double paddle_width;
    QGraphicsScene *scene;
    QMap<int,bool> keys;
};

#endif // PADDLE_H
