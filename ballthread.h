#ifndef BALLTHREAD_H
#define BALLTHREAD_H
#include <QThread>
#include <QObject>
#include <QGraphicsScene>
#include "ball.h"
class ballthread : public QThread
{
    Q_OBJECT
public:
    ballthread(Ball* b,QGraphicsScene* ptr);
    ~ballthread();
    Ball* ball;
private:
    int id;
    QGraphicsScene* scene;
    double screen_width;
    double screen_height;
    void wall_collision();
    int paddle_collision();
    void brick_collision();
    void ball_move();
    void timerEvent(QTimerEvent *);
public slots:
    void PaddleCollisionDetected(bool left_corner,bool right_corner);
signals:
    void endgame();


};
#endif // BALLTHREAD_H
