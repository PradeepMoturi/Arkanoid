#ifndef OBJECTLOCKER_H
#define OBJECTLOCKER_H

#include "ball.h"
#include <QMutex>

class ObjectLocker
{
public:
    ObjectLocker();
    QMutex mutex;
    std::vector <Ball*> ball_list;
    void remove(Ball *ball);
    void push(Ball *ball);
};

#endif // OBJECTLOCKER_H
