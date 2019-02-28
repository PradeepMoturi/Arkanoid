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
#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "backgroundmusic.h"
#include "score.h"
#include "ball.h"
#include "gridlayout.h"
#include "powerup.h"
#include "ballworker.h"
#include <vector>
#include "powerup.h"

class Game:public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget *parent=nullptr);
    ~Game();
    QGraphicsScene *scene;
    Score *score;
    void mainConnections(ballworker* worker);
    void sideConnections(ballworker* worker);
    void removeConnections(ballworker* worker);
    void powerConnections(Powerup* power);
    void remove_brick(Brick *brick);
signals:
    void pausemusic();
    void resumemusic();

public slots:
    void ballpositionupdater(Ball*b, double x, double y);
    void build();
    void start();
    void restart();
    void end(ballworker*,Ball*);
    void pause();
    void removepowerup(Powerup*);
    void Multiply_ball();
    void updateStatus();
private:
    int fire_time=0;
    bool status=false;
    void brick_collision(Ball* b);
    Ball* ball;
    std::vector <Ball*> ball_list;
    std::vector <ballworker*> worker_list;
    std::vector<Powerup*> power_list;
    void setup_scene();
    gridlayout* grid;
    QTimer *timer;
    void createGrid(int rows,int columns);
    BackgroundMusic* music;
};

#endif // GAME_H
