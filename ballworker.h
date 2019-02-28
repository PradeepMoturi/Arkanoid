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
#ifndef BALLWORKER_H
#define BALLWORKER_H
#include <QThread>
#include <QObject>
#include <QGraphicsScene>
#include "ball.h"
#include "brick.h"
class ballworker : public QObject
{
    Q_OBJECT
public:
    ballworker(QGraphicsScene* curr,Ball *b);
    ~ballworker();
    Ball* ball;
private:
    int id;
    double screen_width;
    double screen_height;
    void wall_collision();
    int paddle_collision();
    void brick_collision();
public slots:
    void ball_move();
    void PaddleCollisionDetected(Ball* nball,bool left_corner,bool right_corner);
signals:
    void ballposupdater(Ball* nball,double x, double y);
    void endgame(ballworker*,Ball* nball);
//    void destroy(Brick* nbrick);
};
#endif // BALLWORKER_H
