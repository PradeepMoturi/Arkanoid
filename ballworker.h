#ifndef BALLWORKER_H
#define BALLWORKER_H
#include <QThread>
#include <QObject>
#include <QGraphicsScene>
#include "ball.h"
#include "brick.h"
class ballworker : public QObject
{
    Q_OBJECT
public:
    ballworker(QGraphicsScene* curr,Ball *b);
    ~ballworker();
    Ball* ball;
private:
    int id;
    double screen_width;
    double screen_height;
    void wall_collision();
    int paddle_collision();
    void brick_collision();
public slots:
    void ball_move();
    void PaddleCollisionDetected(Ball* nball,bool left_corner,bool right_corner);
signals:
    void ballposupdater(Ball* nball,double x, double y);
    void endgame(ballworker*,Ball* nball);
    void destroy(Brick* nbrick);
};
#endif // BALLWORKER_H
