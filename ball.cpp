#include "ball.h"
#include "game.h"
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

extern Game* game;

Ball::Ball(QGraphicsItem *parent):QGraphicsEllipseItem(parent){
    ball_radius=20;
    x_velocity=1;
    y_velocity=-1;
    setRect(0,0,ball_radius,ball_radius);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    setPos(game->width()/2-this->radius()/2,game->height()-30-this->radius());
//    setPos(400,800);
}

double Ball::radius()
{
    return ball_radius;
}

void Ball::move()
{
     setPos(x()+this->x_velocity,y()+this->y_velocity);

     qDebug()<<"After deletion signal\n";

     wall_collision();

//     paddle_collision();
}

void Ball::wall_collision()
{
    double screenW = game->width();
    double screenH = game->height();

    // left edge
    if (mapToScene(rect().topLeft()).x() <= 0){
        x_velocity = -1 * x_velocity;
    }

    // right edge
    if (mapToScene(rect().topRight()).x() >= screenW){
        x_velocity = -1 * x_velocity;
    }

    // top edge
    if (mapToScene(rect().topLeft()).y()<= 0){
        y_velocity = -1 * y_velocity;
    }

    //bottom edge
    if (mapToScene(rect().topLeft()).y() >= screenH){
        emit(endgame());
        game->scene->removeItem(this);
        delete this;
        qDebug()<<"Item deleted\n";
    }
}
