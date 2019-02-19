#include "ballworker.h"
#include <QDebug>
#include <QTimer>
#include <QObject>

BallWorker::BallWorker(){

}

void BallWorker::process()
{
    for(int i=0;i<100;i++)
    {
        qDebug()<<" thread \n";
    }
}
