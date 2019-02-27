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
#include "objectlocker.h"
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

    locker=new ObjectLocker();

    QThread* thread = new QThread(this);
    ballworker* worker = new ballworker(scene,ball);

    worker->moveToThread(thread);
    thread->start();

    locker->push(ball);
    worker_list.push_back(worker);

    //create a grid of blocks of size m*n
    grid = new gridlayout(scene,1);

    timer = new QTimer(this);
    timer->start(5);
    connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));

    connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
    connect(worker,SIGNAL(endgame(ballworker*,QGraphicsScene*,Ball*)),this,SLOT(end(ballworker*,QGraphicsScene*,Ball*)));
    connect(worker,SIGNAL(ballposupdater(Ball*,double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));

    connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
    connect(paddle,SIGNAL(multiballadd(QGraphicsScene*,Powerup*)),this,SLOT(Multiply_ball(QGraphicsScene*,Powerup*)));
    connect(paddle,SIGNAL(multiballadd(QGraphicsScene*,Powerup*)),this,SLOT(removepowerup(QGraphicsScene*,Powerup*)));
    connect(paddle,SIGNAL(stop()),this,SLOT(pause()));

    this->show();
}

void Game::ballpositionupdater(Ball* b,double x, double y)
{
    b->setPos(x,y);
    brick_collision(b);
}

void Game::remove_brick(Brick *brick)
{
    //thread-safe I think

    brick->decHits();

    if(brick->getHits()==1)
    {
        brick->update();
    }

    else
    {
        scene->removeItem(brick);
        delete brick;
    }
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
    qDebug()<<"Restart";
    scene->clear();
    this->build();
}

void Game::end(ballworker* nworker,QGraphicsScene* nscene,Ball *nball)
{
    //mutliple balls on reaching the bottom send the signal

    //ball_list.size() must be mutually excluded

    //below delete operation has to be performed with locks ??

    qDebug()<<"Ball List size before erasing: "<<locker->ball_list.size()<<"\n";
    size_t x=locker->ball_list.size();
    locker->remove(nball);
    size_t y=locker->ball_list.size();
    qDebug()<<"Ball List size after erasing: "<<locker->ball_list.size()<<"\n";

    if(x!=y)
    {
        disconnect(nworker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
        disconnect(nworker,SIGNAL(endgame(ballworker*,QGraphicsScene*,Ball*)),this,SLOT(end(ballworker*,QGraphicsScene*,Ball*)));
        disconnect(nworker,SIGNAL(ballposupdater(Ball*,double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));
        disconnect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),nworker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
        disconnect(timer,SIGNAL(timeout()),nworker,SLOT(ball_move()));
        //scene->removeItem(nball);
        //worker_list.erase(std::remove(worker_list.begin(),worker_list.end(),nworker),worker_list.end());
        delete nworker;
        //delete nball;
    }

    if(locker->ball_list.size()==0)
    {
        end_menu *emenu = new end_menu();
        this->hide();
        emenu->show();
        return;
    }
}

Game::~Game()
{
    music->exit();
    delete music;
}
void Game::brick_collision(Ball* nball)
{
    //multiple balls handle this section ?
    // this is one of the critical section
    //thread unsafe

    QList<QGraphicsItem*> cItems = nball->collidingItems();

    for (int i = 0, n = cItems.size(); i < n; ++i){
            Brick* brick = dynamic_cast<Brick*>(cItems[i]);
            // collides with brick
            if (brick){
                double ballx = nball->pos().x();
                double bally = nball->pos().y();
                double brickx = brick->pos().x();
                double bricky = brick->pos().y();

                // collides from bottom
                if (bally >= bricky + brick->getHeight() && nball->y_velocity < 0){
                    nball->y_velocity = -1 * nball->y_velocity;
                }

                // collides from top
                if (bricky >= bally + nball->rect().height() && nball->y_velocity > 0 ){
                    nball->y_velocity = -1 * nball->y_velocity;
                }

                // collides from right
                if (ballx >= brickx + brick->getWidth() && nball->x_velocity < 0){
                    nball->x_velocity = -1 * nball->x_velocity;
                }

                // collides from left
                if (brickx >= ballx + nball->rect().width()  && nball->x_velocity > 0){
                    nball->x_velocity = -1 * nball->x_velocity;
                }
                this->score->increase();

                brick->decHits(); //decreases the hits

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
    //multiple balls handle this code section also

    long unsigned number_of_balls = locker->ball_list.size();
    qDebug()<<number_of_balls<<"A'''";
    if(locker->ball_list.size()>=10) return;
    //do not create the ball in the main scene ??
    QThread* thread = new QThread();
    for(long unsigned i = 0;i< number_of_balls ; i++)
    {
//        if(locker->ball_list.size()>=30) return;
        Ball* new_ball = new Ball();
        scene->addItem(new_ball);

        new_ball->setPos(locker->ball_list[i]->x(),locker->ball_list[i]->y());

        ballworker* worker = new ballworker(scene,new_ball);

        worker->moveToThread(thread);

        locker->push(new_ball);
        worker_list.push_back(worker);

        QObject::connect(paddle,SIGNAL(ballCollision(Ball*,bool,bool)),worker,SLOT(PaddleCollisionDetected(Ball*,bool,bool)));
        connect(worker,SIGNAL(destroy(Brick*)),this,SLOT(remove_brick(Brick*)));
        connect(worker,SIGNAL(endgame(ballworker*,QGraphicsScene*,Ball*)),this,SLOT(end(ballworker*,QGraphicsScene*,Ball*)));
        connect(timer,SIGNAL(timeout()),worker,SLOT(ball_move()));
        connect(worker,SIGNAL(ballposupdater(Ball*, double, double)),this,SLOT(ballpositionupdater(Ball*,double, double)));
    }
    thread->start();

}

void Game::removepowerup(QGraphicsScene *nscene,Powerup* power)
{
    //not a critical section code

    disconnect(timer,SIGNAL(timeout()),power,SLOT(powerup_move()));
    qDebug()<<"Powerup Size before deleting "<<power_list.size()<<"\n";
    power_list.erase(std::remove(power_list.begin(),power_list.end(),power),power_list.end());
    qDebug()<<"Powerup Size before deleting "<<power_list.size()<<"\n";
    nscene->removeItem(power);
    delete power;
}
