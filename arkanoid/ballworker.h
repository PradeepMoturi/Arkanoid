#ifndef BALLWORKER_H
#define BALLWORKER_H

#include <QObject>

class BallWorker:public QObject
{
    Q_OBJECT
public:
    BallWorker();
public slots:
    void process();
};

#endif // BALLWORKER_H
