#include "powerup.h"
#include <QBrush>
#include <QDebug>
Powerup::Powerup(QGraphicsItem *parent):QGraphicsRectItem (parent)
{
    x_velocity = 0;
    y_velocity = 1;
    powerup_width=50;
    powerup_height=8;
    setRect(0,0,powerup_width,powerup_height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
};
void Powerup::set(int id,double x, double y)
{
    powerup_id = id;
    setPos(x,y);
}

void Powerup::powerup_move()
{
    qreal temp = 700;

    setPos(x(),y()+y_velocity);
    if (y()> temp)
    {
        emit remove_connection(this);
    }
}
double Powerup::getwidth()
{
    return powerup_width;
}

double Powerup::getheight()
{
    return powerup_height;
}
