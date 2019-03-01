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
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QBrush>
#include <QColor>
#include <QApplication>
#include <QGraphicsRectItem>
#include "backgroundmusic.h"
#include <QImage>
#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "startpage.h"
#include "pausemenu.h"
#include "endmenu.h"
#include "brick.h"
#include "ballworker.h"
#include "powerup.h"
#include <algorithm>
#include <math.h>

extern Paddle* paddle;

Game::Game(QWidget *parent):QGraphicsView (parent)
{
    setup_scene();
    QApplication::setKeyboardInputInterval(5);
    music = new BackgroundMusic();
};

void Game::setup_scene()
{
    scene=new QGraphicsScene(0,0,700,700,this);
    setScene(scene);
    /* https://www.pexels.com/photo/blue-universe-956981/ -> url of image -> Felix Mittermeier */
    setBackgroundBrush(QBrush(QImage(":/Images/background_space.jpg")));
    setFixedSize(700, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::build()
{
    music->start();
    paddle = new Paddle();
    scene->addItem(paddle);

    ball = new Ball();
    scene->addItem(ball);

    status=false;
    fire_time=0;

    score = new Score();
    scene->addItem(score);

    QThread* thread = new QThread(this);
    ballworker* worker = new ballworker(scene,ball);

    worker->moveToThread(thread);
    thread->start();

    ball_list.resize(0);
    worker_list.resize(0);
    ball_list.push_back(ball);
    worker_list.push_back(worker);

    //create a grid of blocks of size m*n
    grid = new gridlayout(scene,1);

    timer = new QTimer(this);
    timer->start(5);

    mainConnections(worker);

    this->show();
}

void Game::ballpositionupdater(Ball* nball,double x, double y)
{
    nball->setPos(x,y);
    brick_collision(nball);

    if(fire_time>=700)
    {
        status=false;
        fire_time=0;
    }

    if(status) fire_time++;
}

void Game::updateStatus()
{
    status=true;
    fire_time=0;
}

void Game::mainConnections(ballworker *worker)
{
    connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));
//    connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    connect(worker,SIGNAL(endgame(ballworker*,Ball*)),this,SLOT(end(ballworker*,Ball*)));
    connect(worker,SIGNAL(ballposupdater(Ball*,double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));

    connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
    connect(paddle,SIGNAL(multiballadd()),this,SLOT(Multiply_ball()));
    connect(paddle,SIGNAL(destroy_powerup(Powerup*)),this,SLOT(removepowerup(Powerup*)));
    connect(paddle,SIGNAL(stop()),this,SLOT(pause()));
    connect(this,SIGNAL(brick_sound()),music,SLOT(Brick_Sound()));
    connect(paddle,SIGNAL(sendStatus()),this,SLOT(updateStatus()));

    connect(this,SIGNAL(pausemusic()),music,SLOT(pausemusic()));
    connect(this,SIGNAL(resumemusic()),music,SLOT(resumemusic()));
    connect(this,SIGNAL(restartmusic()),music,SLOT(restartmusic()));

}

void Game::sideConnections(ballworker *worker)
{
    connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));

//    connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    connect(worker,SIGNAL(endgame(ballworker*,Ball*)),this,SLOT(end(ballworker*,Ball*)));
    connect(worker,SIGNAL(ballposupdater(Ball*, double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));

    connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
}

void Game::removeConnections(ballworker *worker)
{
    //disconnect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    disconnect(worker,SIGNAL(endgame(ballworker*,Ball*)),this,SLOT(end(ballworker*,Ball*)));
    disconnect(worker,SIGNAL(ballposupdater(Ball*,double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));
    disconnect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
    disconnect(paddle,SIGNAL(sendStatus()),this,SLOT(updateStatus()));
    disconnect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));
}

void Game::powerConnections(Powerup *power)
{
    connect(timer,SIGNAL(timeout()),power,SLOT(powerup_move()));
    connect(power,SIGNAL(remove_connection(Powerup*)),this,SLOT(removepowerup(Powerup*)));
}

void Game::remove_brick(Brick *brick)
{
    brick->decHits();

    if(brick->getHits()==1){brick->update();}

    else
    {
        if(brick->brick_id!=0)
        {
               Powerup* power = new Powerup();
               power->set(brick->brick_id,brick->x()+(brick->getWidth()/2)-(power->getwidth()/2),brick->y()+brick->getHeight());
               scene->addItem(power);

               power_list.push_back(power);
               powerConnections(power);
        }

        scene->removeItem(brick);
        delete brick;
    }
}

void Game::removepowerup(Powerup* power)
{
    disconnect(timer,SIGNAL(timeout()),power,SLOT(powerup_move()));
    power_list.erase(std::remove(power_list.begin(),power_list.end(),power),power_list.end());
    scene->removeItem(power);
    delete power;
}

void Game::end(ballworker* nworker,Ball *nball)
{
    size_t x=ball_list.size();
    ball_list.erase(std::remove(ball_list.begin(),ball_list.end(),nball),ball_list.end());
    size_t y=ball_list.size();

    if(x!=y)
    {
        removeConnections(nworker);
        scene->removeItem(nball);
        worker_list.erase(std::remove(worker_list.begin(),worker_list.end(),nworker),worker_list.end());
        delete nworker;
        //delete nball;
    }

    if(ball_list.size()==0)
    {
        emit(pausemusic());
        EndMenu *emenu = new EndMenu();
        this->hide();
        emenu->show();
        return;
    }
}

void Game::brick_collision(Ball* nball)
{
    QList<QGraphicsItem*> cItems = nball->collidingItems();

    for (int i = 0, n = cItems.size(); i < n; ++i){
            Brick* brick = dynamic_cast<Brick*>(cItems[i]);
            if (brick){
                double ballx = nball->pos().x();
                double bally = nball->pos().y();
                double brickx = brick->pos().x();
                double bricky = brick->pos().y();

                //status different ignore

                if(!status)
                {
                    if (bally >= bricky + brick->getHeight() && nball->get_yvelocity() < 0){
                        nball->set_yvelocity(true);
                    }

                    if (bricky >= bally + nball->rect().height() && nball->get_yvelocity() > 0 ){
                        nball->set_yvelocity(false);
                    }

                    if (ballx >= brickx + brick->getWidth() && nball->get_xvelocity() < 0){
                        nball->set_xvelocity(true);
                    }

                    if (brickx >= ballx + nball->rect().width()  && nball->get_xvelocity() > 0){
                        nball->set_xvelocity(false);
                    }
                }

                score->increase();
                emit(brick_sound());

                remove_brick(brick);
            }
        }
}

void Game::Multiply_ball()
{
    long unsigned number_of_balls = ball_list.size();
    if(ball_list.size()>=10) return;

    QThread* thread = new QThread(this);

    for(long unsigned i = 0;i< number_of_balls ; i++)
    {
        Ball* new_ball = new Ball();
        ballworker* worker = new ballworker(scene,new_ball);

        worker->moveToThread(thread);

        ball_list.push_back(new_ball);
        worker_list.push_back(worker);

        new_ball->setPos(ball_list[i]->x(),ball_list[i]->y());
        double vel_x = ball_list[i]->get_xvelocity();

        if(vel_x>0) new_ball->set_xvelocity(false);
        else new_ball->set_xvelocity(true);

        scene->addItem(new_ball);

        sideConnections(worker);

    }
    thread->start();
}

void Game::start()
{
    timer->start(5);
    emit(resumemusic());
}

void Game::pause()
{
    PauseMenu *pmenu=new PauseMenu();
    emit(pausemusic());
    //music->start();
    timer->stop();
    pmenu->show();
}

void Game::restart()
{
    scene->clear();
    emit(restartmusic());
    this->build();
}

Game::~Game()
{
    music->exit();
    delete music;
}
