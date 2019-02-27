#include "objectlocker.h"

ObjectLocker::ObjectLocker(){}

void ObjectLocker::remove(Ball *ball)
{
    mutex.lock();
    ball_list.erase(std::remove(ball_list.begin(),ball_list.end(),ball),ball_list.end());
    mutex.unlock();
}

void ObjectLocker::push(Ball *ball)
{
    mutex.lock();
    ball_list.push_back(ball);
    mutex.unlock();
}
