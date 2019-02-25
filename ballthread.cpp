#include <QDebug>
#include "ballthread.h"

ballthread::ballthread(Ball* b,QGraphicsScene* ptr)
{
    scene = ptr;
    ball = b;
    screen_width = scene->width();
    screen_height = scene->height();
    startTimer(5);
}
ballthread ::~ballthread()
{

}
void ballthread::timerEvent(QTimerEvent *)
{
    ball_move();
}
void ballthread::ball_move()
{
    wall_collision();
    //brick_collision();
    ball->setPos(ball->x()+ball->x_velocity,ball->y()+ball->y_velocity);
}

void ballthread::PaddleCollisionDetected(bool left_corner,bool right_corner)
{

       if(left_corner == false&&right_corner==false)
       {
           ball->y_velocity = -abs(ball->y_velocity);
       }
       else if(left_corner==true)
       {
           ball->x_velocity = -abs(ball->x_velocity);
       }
       else
       {
           ball->x_velocity = abs(ball->x_velocity);
       }
}
void ballthread::wall_collision()
{

    // left edge
    if (ball->mapToScene(ball->rect().topLeft()).x() <= 0)
    {
        ball->x_velocity = -1 * ball->x_velocity;
    }

    // right edge
    if (ball->mapToScene(ball->rect().topRight()).x() >= screen_width)
    {
        ball->x_velocity = -1 * ball->x_velocity;
    }

    // top edge
    if (ball->mapToScene(ball->rect().topLeft()).y()<= 0)
    {
        ball->y_velocity = -1 * ball->y_velocity;
    }

    //bottom edge
    if (ball->mapToScene(ball->rect().topRight()).y()>screen_height)
    {
        scene->removeItem(ball);
        //emit(endgame());
        //delete ball;
        delete this;
        qDebug()<<"Item deleted\n";
        return;
    }
}

//void ballthread::brick_collision()
//{
//    QMutex mutex;
//    QMutexLocker locker(&mutex);

//    QList<QGraphicsItem*> cItems = collidingItems();

//    for (int i = 0, n = cItems.size(); i < n; ++i){
//            Brick* brick = dynamic_cast<Brick*>(cItems[i]);
//            // collides with brick
//            if (brick){
//                double ballx = pos().x();
//                double bally = ball->pos().y();
//                double brickx = brick->pos().x();
//                double bricky = brick->pos().y();

//                // collides from bottom
//                if (bally >= bricky + brick->getHeight() && y_velocity < 0){
//                    y_velocity = -1 * y_velocity;
//                }

//                // collides from top
//                if (bricky >= bally + rect().height() && y_velocity > 0 ){
//                    y_velocity = -1 * y_velocity;
//                }

//                // collides from right
//                if (ballx >= brickx + brick->getWidth() && x_velocity < 0){
//                    x_velocity = -1 * x_velocity;
//                }

//                // collides from left
//                if (brickx >= ballx + rect().width()  && x_velocity > 0){
//                    x_velocity = -1 * x_velocity;
//                }

//                brick->setHits(brick->getHits()-1);

//                if(brick->getHits()==1)
//                {
//                    brick->update();
//                }

//                else {
//                    game->scene->removeItem(brick);
//                    delete brick;
//                }
//            }
//        }

//}
