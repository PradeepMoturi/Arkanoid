#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class Powerup:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    Powerup(QGraphicsItem* parent = nullptr);
    void set(int id, double x, double y);
    int powerup_id;
    double getwidth();
    double getheight();
private:
    double x_velocity;
    double y_velocity;
    double powerup_width;
    double powerup_height;
signals:
    void remove_connection(Powerup*);
public slots:
    void powerup_move();
};

#endif // POWERUP_H
