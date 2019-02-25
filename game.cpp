#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "start_menu.h"
#include "pause_menu.h"
#include "end_menu.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QBrush>
#include <QColor>
#include <QApplication>


extern Paddle* paddle;
extern start_menu *smenu;
extern Game *game;

Ball *ball;

Game::Game(QWidget *parent):QGraphicsView (parent)
{
    scene=new QGraphicsScene(0,0,700,700,this);
   // QPixmap pix(":/img/test.png");
    //QBrush bkg;
    //QColor bc;
    //bc.setBlue(20);
    //bkg.setColor(bc);
    //scene->setBackgroundBrush(bkg);
    setScene(scene);
    setFixedSize(700, 700);
    //bkg.setTexture(pix.scaled(700,700,Qt::KeepAspectRatioByExpanding));
    //scene->setBackgroundBrush(bkg);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QApplication::setKeyboardInputInterval(5);

};

void Game::build()
{
    //deleting the previous menu derived from the QGraphicsScene
    //menu depending . can be start or end menu ??
    paddle = new Paddle();
    scene->addItem(paddle);
    ball=new Ball();
    scene->addItem(ball);
    QThread *thread=new QThread;
    QTimer *timer=new QTimer(nullptr);
    timer->setInterval(5);
    timer->moveToThread(thread);
    connect(thread,SIGNAL(started()),timer,SLOT(start()));
    connect(timer,SIGNAL(timeout()),ball,SLOT(move()));
    connect(ball,SIGNAL(endgame()),this,SLOT(end()));
    connect(this,SIGNAL(stop()),timer,SLOT(stop()));
    connect(this,SIGNAL(start()),timer,SLOT(start()));
    thread->start();
    this->show();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left)
    {
        paddle->move_paddle(-20);
    }

    else if(event->key()==Qt::Key_Right)
    {
        paddle->move_paddle(20);
    }

    else if(event->key()==Qt::Key_Escape)
    {
        pause_menu *pmenu=new pause_menu();
        pmenu->show();
        emit stop();
    }
}

void Game::restart()
{
    scene->clear();
    this->build();
}

void Game::end()
{
    end_menu *emenu = new end_menu();
    emit stop();
    this->hide();
    emenu->show();
}



