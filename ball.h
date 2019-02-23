#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>
#include <QThread>

class Ball:public QObject,public QGraphicsEllipseItem{
Q_OBJECT
public:
    Ball(QGraphicsItem *parent=NULL);
    double radius();
    void play();
    int wall_collision();
    int paddle_collision();
signals:
    void endgame();
    void reachedBottom(qreal x,qreal y, double radius);
    //void reachedBottom(Ball b);
public slots:
    void move();
    void PaddleCollisionDetected(int direction,bool left, bool right);

private:
    double ball_radius;
    double x_velocity;
    double y_velocity;
};

#endif // BALL_H
