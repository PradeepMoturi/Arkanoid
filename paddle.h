#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QObject>
#include"powerup.h"
class Paddle:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    Paddle(QGraphicsItem *parent=nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent* event);
    void move_paddle(double x);
    qreal height();
    qreal width();
    double getCenterX();
    double rightCornerX();
    double leftCornerX();

    void timerEvent(QTimerEvent *);
    void CollisionChecker();//(qreal x,qreal y, double radius);
signals:
    void multiballadd(Powerup*);
    void stop();
    void stop_game();
    void ballCollision(bool left_corner,bool right_corner);
private:
    int cnt = 0;
    bool foo = true;
    double paddle_height;
    double paddle_width;
    QMap<int,bool> keys;
};

#endif // PADDLE_H
