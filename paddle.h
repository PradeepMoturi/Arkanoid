#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QObject>

class Paddle:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    Paddle(QGraphicsItem *parent=NULL);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent* event);
    void move_paddle(double x);
    double height();
    double width();
    void timerEvent(QTimerEvent *);
public slots:
    void CollisionChecker(qreal x,qreal y, double radius);
signals:
    void stop_game();
    void ballCollision(int direction,bool left, bool right);
private:
    double paddle_height;
    double paddle_width;
    QMap<int,bool> keys;
};

#endif // PADDLE_H
