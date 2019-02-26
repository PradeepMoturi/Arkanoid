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
//    qDebug()<<"Powerup moved";
//    qDebug()<<"Powerup moved";

    setPos(x(),y()+y_velocity);
    if (y()> temp)
    {
        qDebug()<<"Power up reached Bottom Edge";
        qDebug()<<"Item deleted\n";
        emit remove_connection(this);
        delete this;
    }

}
