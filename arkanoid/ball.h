#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QObject>

class Ball:public QObject,public QGraphicsEllipseItem{
Q_OBJECT
public:
    Ball(QGraphicsItem *parent=NULL);
    double radius();
    void play();
public slots:
    void move();
private:
    double ball_radius;
};

#endif // BALL_H
