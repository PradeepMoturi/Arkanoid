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
    ballworker(Ball* b,QGraphicsScene* ptr);
    ~ballworker();
    Ball* ball;
private:
    int id;
    QGraphicsScene* scene;
    double screen_width;
    double screen_height;
    void wall_collision();
    int paddle_collision();
    void brick_collision();
public slots:
    void ball_move();
    void PaddleCollisionDetected(bool left_corner,bool right_corner);
signals:
    void endgame();
    void destroy(Brick*);


};
#endif // BALLWORKER_H