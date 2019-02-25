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
#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "start_menu.h"
#include "pause_menu.h"
#include "end_menu.h"
#include "brick.h"
#include "ballthread.h"

extern Paddle* paddle;
extern start_menu *smenu;
extern Game *game;

Ball *ball;

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
    setFixedSize(700, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}
void Game::build()
{
    //deleting the previous menu derived from the QGraphicsScene
    //menu depending . can be start or end menu ??
    music->start();
    paddle = new Paddle();
    scene->addItem(paddle);

    ball=new Ball();
    scene->addItem(ball);
    ballthread* worker1 = new ballthread(ball,scene);
    worker1->start();


    QObject::connect(paddle,SIGNAL(ballCollision(bool,bool)),worker1,SLOT(PaddleCollisionDetected(bool,bool)));

    //create a grid of blocks of size m*n

    grid = new gridlayout(9,6,scene);
  
    QThread *thread=new QThread;
    QTimer *timer=new QTimer(nullptr);

    timer->setInterval(5);
    timer->moveToThread(thread);

    connect(thread,SIGNAL(started()),timer,SLOT(start()));
    connect(timer,SIGNAL(timeout()),ball,SLOT(move()));

    connect(ball,SIGNAL(endgame()),timer,SLOT(stop()));
    connect(ball,SIGNAL(endgame()),this,SLOT(end()));

    connect(paddle,SIGNAL(stop()),timer,SLOT(stop()));
    connect(this,SIGNAL(start()),timer,SLOT(start()));

    thread->start();

    this->show();
}

void Game::pause()
{
    pause_menu *pmenu=new pause_menu();
    pmenu->show();
}

void Game::restart()
{
    scene->clear();
    this->build();
}

void Game::end()
{
    end_menu *emenu = new end_menu();
    this->hide();
    emenu->show();
}

Game::~Game()
{
    music->exit();
    delete music;
}
