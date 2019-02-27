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
extern Game *game;


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
    paddle = new Paddle(scene);
    scene->addItem(paddle);

    ball = new Ball();
    scene->addItem(ball);

    // Adding Score to the Scene
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
    connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));

    connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    connect(worker,SIGNAL(endgame(QGraphicsScene*,Ball*)),this,SLOT(end(QGraphicsScene*,Ball*)));
    connect(worker,SIGNAL(ballposupdater(Ball*,double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));

    connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
    connect(paddle,SIGNAL(multiballadd(QGraphicsScene*,Powerup*)),this,SLOT(Multiply_ball(QGraphicsScene*,Powerup*)));
    connect(paddle,SIGNAL(multiballadd(QGraphicsScene*,Powerup*)),this,SLOT(removepowerup(QGraphicsScene*,Powerup*)));

    this->show();
}

void Game::ballpositionupdater(Ball* b,double x, double y)
{
    b->setPos(x,y);
    brick_collision();
}

void Game::remove_brick(Brick *brick)
{

    brick->setHits(brick->getHits()-1);

    if(brick->getHits()==1)
    {
        brick->update();
    }

    else {
        scene->removeItem(brick);
        delete brick;
    }
}

void Game::pause()
{
    pause_menu *pmenu=new pause_menu();

    pmenu->show();
}

void Game::restart()
{
    qDebug()<<"Restart";
    scene->clear();
    this->build();
}

void Game::end(QGraphicsScene* nscene,Ball *nball)
{
    if(ball_list.size()==0)
    {
        end_menu *emenu = new end_menu();
        this->hide();
        emenu->show();
    }

    qDebug()<<"Ball List size before erasing: "<<ball_list.size()<<"\n";
    ball_list.erase(std::remove(ball_list.begin(),ball_list.end(),nball),ball_list.end());
    qDebug()<<"Ball List size after erasing: "<<ball_list.size()<<"\n";
    nscene->removeItem(nball);
    delete nball;
}

Game::~Game()
{
    music->exit();
    delete music;
}
void Game::brick_collision()
{
    QList<QGraphicsItem*> cItems = ball->collidingItems();

    for (int i = 0, n = cItems.size(); i < n; ++i){
            Brick* brick = dynamic_cast<Brick*>(cItems[i]);
            // collides with brick
            if (brick){
                double ballx = ball->pos().x();
                double bally = ball->pos().y();
                double brickx = brick->pos().x();
                double bricky = brick->pos().y();

                // collides from bottom
                if (bally >= bricky + brick->getHeight() && ball->y_velocity < 0){
                    ball->y_velocity = -1 * ball->y_velocity;
                }

                // collides from top
                if (bricky >= bally + ball->rect().height() && ball->y_velocity > 0 ){
                    ball->y_velocity = -1 * ball->y_velocity;
                }

                // collides from right
                if (ballx >= brickx + brick->getWidth() && ball->x_velocity < 0){
                    ball->x_velocity = -1 * ball->x_velocity;
                }

                // collides from left
                if (brickx >= ballx + ball->rect().width()  && ball->x_velocity > 0){
                    ball->x_velocity = -1 * ball->x_velocity;
                }
                this->score->increase();
          //      emit destroy(brick);

                brick->setHits(brick->getHits()-1);

                if(brick->getHits()==1)
                {
                    brick->update();
                }

                else
                {
                    if(brick->brick_id!=0)
                    {
                           Powerup* power = new Powerup(scene);
                           scene->addItem(power);
                           power->set(brick->brick_id,brick->x(),brick->y());
                           qDebug()<<brick->x()<<" "<<brick->y();
                           power_list.push_back(power);
                           connect(timer,SIGNAL(timeout()),power,SLOT(powerup_move()));
                           connect(power,SIGNAL(remove_connection(QGraphicsScene*,Powerup*)),this,SLOT(removepowerup(QGraphicsScene*,Powerup*)));
                    }
                    scene->removeItem(brick);
                    delete brick;
                }
            }
        }
}

void Game::Multiply_ball(QGraphicsScene *nscene,Powerup* power)
{
    long unsigned number_of_balls = ball_list.size();
    qDebug()<<number_of_balls<<"A'''";

    //do not create the ball in the main scene ??

    for(long unsigned i = 0;i< number_of_balls ; i++)
    {
        Ball* new_ball = new Ball();
        nscene->addItem(new_ball);

        new_ball->setPos(ball_list[i]->x(),ball_list[i]->y());
        QThread* thread = new QThread();

        ballworker* worker = new ballworker(nscene,new_ball);

        worker->moveToThread(thread);
        thread->start();

        ball_list.push_back(new_ball);
        worker_list.push_back(worker);

        QObject::connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
        connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
        connect(worker,SIGNAL(endgame(QGraphicsScene*,Ball*)),this,SLOT(end(QGraphicsScene*,Ball*)));
        connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));
        connect(worker,SIGNAL(ballposupdater(Ball*, double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));
    }
}

void Game::removepowerup(QGraphicsScene *nscene,Powerup* power)
{
    disconnect(timer,SIGNAL(timeout()),power,SLOT(powerup_move()));
    qDebug()<<"Powerup Size before deleting "<<power_list.size()<<"\n";
    power_list.erase(std::remove(power_list.begin(),power_list.end(),power),power_list.end());
    qDebug()<<"Powerup Size before deleting "<<power_list.size()<<"\n";
    nscene->removeItem(power);
    delete power;
}
