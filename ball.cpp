#include "ball.h"
#include "game.h"
#include "paddle.h"
#include "brick.h"
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

extern Game* game;
extern Paddle* paddle;

Ball::Ball(QGraphicsItem *parent):QGraphicsEllipseItem(parent){
    ball_radius=20;
    x_velocity=-1;
    y_velocity=-1;
    setRect(0,0,ball_radius,ball_radius);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    setPos(game->width()/2-this->radius()/2,game->height()-30-this->radius());
}

double Ball::radius()
{
    return ball_radius;
}

void Ball::move()
{
     if(wall_collision()==1) //object is not deleted
     {
        brick_collision();
        paddle_collision();
        setPos(x()+this->x_velocity,y()+this->y_velocity);
     }
}

int Ball::wall_collision()
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
    if (mapToScene(rect().topRight()).y()>game->height()){
        game->scene->removeItem(this);
        emit(endgame());
        delete this;
        qDebug()<<"Item deleted\n";
        return 0;
    }

    return 1;
}

int Ball::paddle_collision()
{
    //handle side paddle collisions

    if(mapToScene(rect().bottomRight()).x()>=paddle->x() && mapToScene(rect().bottomRight()).x()<paddle->x()+0.0001 && mapToScene(rect().bottomRight()).y()>paddle->y())
    {
        x_velocity=-(x_velocity);
        return 0;
    }

    else if(mapToScene(rect().bottomLeft()).x()<=paddle->x()+paddle->width() && mapToScene(rect().bottomLeft()).x()>paddle->x()+paddle->width()-0.0001 && mapToScene(rect().bottomLeft()).y()>paddle->y())
    {
        x_velocity=-(x_velocity);
        return 0;
    }

    //handle upper paddle side collsions

    else if(mapToScene(rect().bottomRight()).x()>paddle->x() && mapToScene(rect().bottomLeft()).x()<paddle->x()+paddle->width())
    {
        if (mapToScene(rect().bottomLeft()).y()>paddle->y()){
            y_velocity=-(y_velocity);
//            double ballX = mapToScene(rect().bottomRight()).x()+this->radius();
//            double paddleX = paddle->x()+paddle->width()/2;
//            double dvx = ballX - paddleX;
            return 0;
        }
    }

    return 1;
}


void Ball::brick_collision()
{
    QMutex mutex;
    QMutexLocker locker(&mutex);

    QList<QGraphicsItem*> cItems = collidingItems();

    for (int i = 0, n = cItems.size(); i < n; ++i){
            Brick* brick = dynamic_cast<Brick*>(cItems[i]);
            // collides with brick
            if (brick){
                double ballx = pos().x();
                double bally = pos().y();
                double brickx = brick->pos().x();
                double bricky = brick->pos().y();

                // collides from bottom
                if (bally >= bricky + brick->getHeight() && y_velocity < 0){
                    y_velocity = -1 * y_velocity;
                }

                // collides from top
                if (bricky >= bally + rect().height() && y_velocity > 0 ){
                    y_velocity = -1 * y_velocity;
                }

                // collides from right
                if (ballx >= brickx + brick->getWidth() && x_velocity < 0){
                    x_velocity = -1 * x_velocity;
                }

                // collides from left
                if (brickx >= ballx + rect().width()  && x_velocity > 0){
                    x_velocity = -1 * x_velocity;
                }

                brick->setHits(brick->getHits()-1);

                if(brick->getHits()==1)
                {
                    brick->update();
                }

                else {
                    game->scene->removeItem(brick);
                    delete brick;
                }
            }
        }

}
