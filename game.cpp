#include "game.h"
#include "ball.h"
#include "paddle.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <QGraphicsRectItem>

extern Paddle* paddle;

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
    paddle = new Paddle();
    scene->addItem(paddle);
    QApplication::setKeyboardInputInterval(5);

    Ball *ball=new Ball();
    scene->addItem(ball);
    //QObject::connect(ball,SIGNAL(reachedBottom(qreal,qreal, double)),paddle,SLOT(CollisionChecker()));
    QObject::connect(paddle,SIGNAL(ballCollision(double,bool)),ball,SLOT(PaddleCollisionDetected(double,bool)));

    QThread *thread=new QThread;
    QTimer *timer=new QTimer(nullptr);
    timer->setInterval(5);
    //timer->moveToThread(thread);
    connect(timer,SIGNAL(timeout()),ball,SLOT(move()));
    connect(thread,SIGNAL(started()),timer,SLOT(start()));
    thread->start();
    connect(ball,SIGNAL(endgame()),timer,SLOT(stop()));
}
