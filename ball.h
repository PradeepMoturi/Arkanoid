#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>
#include <QGraphicsView>
#include <QThread>
#include <QMutex>

class Ball:public QObject,public QGraphicsEllipseItem{
Q_OBJECT
public:
    Ball(QGraphicsItem *parent=nullptr);
    double radius();
    double getCenterX();
    double get_xvelocity();
    double get_yvelocity();
    void set_xvelocity(bool pos);
    void set_yvelocity(bool pos);
    QMutex mutex;
private:
    double ball_radius;
    double x_velocity;
    double y_velocity;
};

#endif // BALL_H
