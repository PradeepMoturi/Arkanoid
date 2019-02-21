#include "ballworker.h"
#include <QDebug>
#include <QTimer>
#include <QObject>
#include "ball.h"
#include "game.h"
#include <QTimer>

BallWorker::BallWorker(QObject *parent)
{
    QTimer *timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    timer->start();
}

void BallWorker::run()
{
    for(int i=0;i<1000;i++)
    {
        qDebug()<<" Thread here\n";
        qDebug()<<"Bye Thread\n";
    }
    qDebug()<<"Who's first?\n";
    exec();
}
