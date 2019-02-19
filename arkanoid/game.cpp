#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "ballworker.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>

Game::Game(QWidget *parent):QGraphicsView (parent)
{
    scene=new QGraphicsScene(0,0,700,700);
    setScene(scene);
    setFixedSize(700, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
};

void Game::start()
{   
    Paddle *paddle = new Paddle();
    scene->addItem(paddle);

    Ball *ball=new Ball();
    scene->addItem(ball);

    QThread *thread=new QThread;
    QTimer *timer=new QTimer(0);
    timer->setInterval(5);
    timer->moveToThread(thread);
    connect(timer,SIGNAL(timeout()),ball,SLOT(move()));
    connect(thread,SIGNAL(started()),timer,SLOT(start()));
    thread->start();
    connect(ball,SIGNAL(endgame()),timer,SLOT(stop()));
}
