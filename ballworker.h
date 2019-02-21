#ifndef BALLWORKER_H
#define BALLWORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "ball.h"

class BallWorker:public QThread
{
    Q_OBJECT
public:
    BallWorker(QObject *parent=NULL);
protected:
    void run();
};

#endif // BALLWORKER_H
