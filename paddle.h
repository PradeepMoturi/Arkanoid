#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QObject>

class Paddle:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    Paddle(QGraphicsItem *parent=nullptr);
    void move_paddle(double x);
    double height();
    double width();
signals:
    void stop_game();
private:
    double paddle_height;
    double paddle_width;
};

#endif // PADDLE_H
