#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QApplication>

#include <QGraphicsRectItem>
#include "backgroundmusic.h"

extern Paddle* paddle;

Game::Game(QWidget *parent):QGraphicsView (parent)
{
    scene=new QGraphicsScene(0,0,700,700);
    setScene(scene);
    setFixedSize(700, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    music = new BackgroundMusic();
};

void Game::start()
{   
    music->start();
    paddle = new Paddle();
    scene->addItem(paddle);
    QApplication::setKeyboardInputInterval(5);

    Ball *ball=new Ball();
    scene->addItem(ball);
    //QObject::connect(ball,SIGNAL(reachedBottom(qreal,qreal, double)),paddle,SLOT(CollisionChecker()));
    QObject::connect(paddle,SIGNAL(ballCollision(double,bool)),ball,SLOT(PaddleCollisionDetected(double,bool)));

    //create a grid of blocks of size m*n

    createGrid(9,6);

    QThread *thread=new QThread;
    QTimer *timer=new QTimer(nullptr);
    timer->setInterval(5);
    //timer->moveToThread(thread);
    connect(timer,SIGNAL(timeout()),ball,SLOT(move()));
    connect(thread,SIGNAL(started()),timer,SLOT(start()));
    thread->start();
    connect(ball,SIGNAL(endgame()),timer,SLOT(stop()));
}

void Game::createGrid(int rows, int columns)
{
   //create grid of size m and n
    double start_x=110;
    double start_y=150;
    double temp_x;
    double temp_y;
    double bheight=20;
    double bwidth=80;

    for(int i=0;i<rows;i++)
    {
        int hits=1;
        temp_x=start_x;
        temp_y=start_y;

        for(int j=0;j<columns;j++)
        {
            if(i==0||i==(rows-1)||j==0||j==(columns-1)) hits=2;
            else hits=1;

            Brick *brick=new Brick(hits);
            brick->setPos(temp_x,temp_y);
            scene->addItem(brick);
            temp_x+=bwidth;
        }

        start_y+=bheight;
    }
}

Game::~Game()
{
    music->exit();
    delete music;
}
