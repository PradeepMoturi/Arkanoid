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

    ball_list.push_back(ball);
    worker_list.push_back(worker1);

    QObject::connect(paddle,SIGNAL(ballCollision(bool,bool)),worker1,SLOT(PaddleCollisionDetected(bool,bool)));

    //create a grid of blocks of size m*n
    grid = new gridlayout(9,6,scene);
    connect(worker1,SIGNAL(endgame()),this,SLOT(end()));
    this->show();
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

void Game::end()
{
    qApp->exit();
    qDebug()<<"Disconnected";
    //disconnect(paddle,SIGNAL(ballCollision(bool,bool)),worker_list[0],SLOT(PaddleCollisionDetected(bool,bool)));
    //disconnect(worker_list[0],SIGNAL(endgame()),this,SLOT(end()));
    //for(unsigned long i = 0 ; i< worker_list.size();i++)
    //{
     //   worker_list[i]->exit();
    //}
    //restart();
    end_menu *emenu = new end_menu();
    this->hide();
    emenu->show();
}

Game::~Game()
{
    music->exit();
    delete music;
}
