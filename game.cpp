#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "start_menu.h"
#include "pause_menu.h"
#include "end_menu.h"
#include "brick.h"
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

extern Paddle* paddle;
extern start_menu *smenu;
extern Game *game;

Ball *ball;

Game::Game(QWidget *parent):QGraphicsView (parent)
{
    scene=new QGraphicsScene(0,0,700,700,this);
    setScene(scene);
    /* https://www.pexels.com/photo/blue-universe-956981/ -> url of image -> Felix Mittermeier */
    setBackgroundBrush(QBrush(QImage(":/Images/background_space.jpg")));
    setFixedSize(700, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QApplication::setKeyboardInputInterval(5);
    music = new BackgroundMusic();


};

void Game::build()
{
    //deleting the previous menu derived from the QGraphicsScene
    //menu depending . can be start or end menu ??
  
    music->start();
    paddle = new Paddle();
    scene->addItem(paddle);
    ball=new Ball();
    scene->addItem(ball);

    // Adding Score to the Scene
    score = new Score();
    scene->addItem(score);

    QObject::connect(paddle,SIGNAL(ballCollision(bool,bool)),ball,SLOT(PaddleCollisionDetected(bool,bool)));

    //create a grid of blocks of size m*n

    createGrid(9,6);
  
  QThread *thread=new QThread;
    QTimer *timer=new QTimer(nullptr);
    timer->setInterval(5);
    timer->moveToThread(thread);
    connect(thread,SIGNAL(started()),timer,SLOT(start()));
    connect(timer,SIGNAL(timeout()),ball,SLOT(move()));
    connect(ball,SIGNAL(endgame()),timer,SLOT(stop()));
    connect(ball,SIGNAL(endgame()),this,SLOT(end()));
    connect(paddle,SIGNAL(stop()),timer,SLOT(stop()));
    connect(paddle,SIGNAL(stop()),this,SLOT(pause()));
    connect(this,SIGNAL(start()),timer,SLOT(start()));
    thread->start();
    this->show();
  
}



//void Game::keyPressEvent(QKeyEvent *event)
//{
//    if(event->key()==Qt::Key_Left)
//    {
//        paddle->move_paddle(-20);
//    }

//    else if(event->key()==Qt::Key_Right)
//    {
//        paddle->move_paddle(20);
//    }

//    else if(event->key()==Qt::Key_Escape)
//    {
//        pause_menu *pmenu=new pause_menu();
//        pmenu->show();
//        emit stop();
//    }
//}

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
