#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "ballworker.h"
#include <QThread>
#include <QObject>
#include <QDebug>

Game::Game(QWidget *parent):QGraphicsView (parent)
{
    scene=new QGraphicsScene(0,0,800,800);
    setScene(scene);
};

void Game::start()
{   
    Paddle *paddle = new Paddle();
    paddle->setPos(this->width()/2-paddle->width()/2,this->height()-30);
    scene->addItem(paddle);

    paddle->setFlag(QGraphicsItem::ItemIsFocusable);
    paddle->setFocus();

    QThread *thread=new QThread();
    Ball *ball=new Ball();
    ball->setPos(this->width()/2-ball->radius()/2,this->height()-30-ball->radius());
    scene->addItem(ball);
    ball->moveToThread(thread);
    connect(thread,SIGNAL(started()),ball,SLOT(move()));
    thread->start();

    for(int i=0;i<1000;i++)
    {
        qDebug()<<"main "<<i<<"\n";
    }
}
