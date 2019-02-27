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
#include "start_menu.h"
#include "pause_menu.h"
#include "end_menu.h"
#include "brick.h"
#include "ballworker.h"
#include "powerup.h"
#include <algorithm>

extern Paddle* paddle;
extern start_menu *smenu;

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

    score = new Score();
    scene->addItem(score);

    QThread* thread = new QThread(this);
    ballworker* worker = new ballworker(scene,ball);

    worker->moveToThread(thread);
    thread->start();

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
}

void Game::mainConnections(ballworker *worker)
{
    connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));

    connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    connect(worker,SIGNAL(endgame(ballworker*,Ball*)),this,SLOT(end(ballworker*,Ball*)));
    connect(worker,SIGNAL(ballposupdater(Ball*,double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));

    connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
    connect(paddle,SIGNAL(multiballadd()),this,SLOT(Multiply_ball()));
    connect(paddle,SIGNAL(destroy_powerup(Powerup*)),this,SLOT(removepowerup(Powerup*)));
    connect(paddle,SIGNAL(stop()),this,SLOT(pause()));
}

void Game::sideConnections(ballworker *worker)
{
    connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));

    connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    connect(worker,SIGNAL(endgame(ballworker*,Ball*)),this,SLOT(end(ballworker*,Ball*)));
    connect(worker,SIGNAL(ballposupdater(Ball*, double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));

    connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
}

void Game::removeConnections(ballworker *worker)
{
    disconnect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    disconnect(worker,SIGNAL(endgame(ballworker*,Ball*)),this,SLOT(end(ballworker*,Ball*)));
    disconnect(worker,SIGNAL(ballposupdater(Ball*,double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));
    disconnect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
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
        end_menu *emenu = new end_menu();
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

                if (bally >= bricky + brick->getHeight() && nball->y_velocity < 0){
                    nball->y_velocity = -1 * nball->y_velocity;
                }

                if (bricky >= bally + nball->rect().height() && nball->y_velocity > 0 ){
                    nball->y_velocity = -1 * nball->y_velocity;
                }

                if (ballx >= brickx + brick->getWidth() && nball->x_velocity < 0){
                    nball->x_velocity = -1 * nball->x_velocity;
                }

                if (brickx >= ballx + nball->rect().width()  && nball->x_velocity > 0){
                    nball->x_velocity = -1 * nball->x_velocity;
                }

                score->increase();

                brick->decHits(); //decreases the hits

                if(brick->getHits()==1) brick->update();

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
        scene->addItem(new_ball);

        sideConnections(worker);
    }

    thread->start();
}

void Game::start()
{
    timer->start(5);
}

void Game::pause()
{
    pause_menu *pmenu=new pause_menu();
    timer->stop();
    pmenu->show();
}

void Game::restart()
{
    scene->clear();
    this->build();
}

Game::~Game()
{
    music->exit();
    delete music;
}
