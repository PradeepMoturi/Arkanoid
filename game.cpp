#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "start_menu.h"
#include "start_menu.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QApplication>

extern Paddle* paddle;
extern start_menu *smenu;

Game::Game(QWidget *parent):QGraphicsView (parent)
{
    scene=new QGraphicsScene(0,0,700,700,this);
    setScene(scene);
    setFixedSize(700, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
};

void Game::start()
{
    //deleting the previous menu derived from the QGraphicsScene

    //menu depending . can be start or end menu ??
    if(smenu!=nullptr)
    {
        smenu->hide();
        smenu->deleteLater();
    }

    paddle = new Paddle();
    scene->addItem(paddle);
    QApplication::setKeyboardInputInterval(5);

    Ball *ball=new Ball();
    scene->addItem(ball);

    show();

    smenu=new start_menu();
    QThread *thread=new QThread;
    QTimer *timer=new QTimer(nullptr);
    timer->setInterval(5);
    timer->moveToThread(thread);
    connect(timer,SIGNAL(timeout()),ball,SLOT(move()));
    connect(thread,SIGNAL(started()),timer,SLOT(start()));
    thread->start();
    connect(ball,SIGNAL(endgame()),timer,SLOT(stop()));
    connect(ball,SIGNAL(endgame()),smenu,SLOT(show()));
    connect(ball,SIGNAL(endgame()),this,SLOT(hide()));
    connect(ball,SIGNAL(endgame()),scene,SLOT(clear()));
}
