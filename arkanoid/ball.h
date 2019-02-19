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
signals:
    void endgame();
public slots:
    void move();
    void wall_collision();
private:
    double ball_radius;
    double x_velocity;
    double y_velocity;
};

#endif // BALL_H
