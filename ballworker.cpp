#include <QDebug>
#include <QtMath>
#include "ballworker.h"
#include "brick.h"

ballworker::ballworker(Ball* b, QGraphicsScene* ptr)
{
    screen_width = ptr->width();
    screen_height = ptr->height();
    scene = ptr;
    ball = b;
    screen_width = 700;
    screen_height = 700;
}
ballworker ::~ballworker()
{

}

void ballworker::ball_move()
{
    //qDebug()<<"Y";
    wall_collision();

    //brick_collision();
//
    //ball->setPos(ball->x()+ball->x_velocity,ball->y()+ball->y_velocity);

    emit(ballposupdater(ball,ball->x()+ball->x_velocity,ball->y()+ball->y_velocity));
}

void ballworker::PaddleCollisionDetected(bool left_corner,bool right_corner)
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
void ballworker::wall_collision()
{

    // left edge
    if (ball->mapToScene(ball->rect().topLeft()).x() <= 0)
    {
        ball->x_velocity = -1 * ball->x_velocity;
    }

    // right edge
    if (ball->mapToScene(ball->rect().topRight()).x() >= screen_width)
    {QList<QGraphicsItem*> cItems = ball->collidingItems();
        ball->x_velocity = -1 * ball->x_velocity;
    }

    // top edge
    if (ball->mapToScene(ball->rect().topLeft()).y()<= 0)
    {
        ball->y_velocity = -1 * ball->y_velocity;
    }

    //bottom edge
    if (ball->mapToScene(ball->rect().topRight()).y()> screen_height)
    {
      //  qDebug()<<"Bottom Edge";
       // qDebug()<<"Item deleted\n";
        emit(endgame());
        return;
    }
}

//void ballworker::brick_collision()
//{
//    QList<QGraphicsItem*> cItems = ball->collidingItems();

//    for (int i = 0, n = cItems.size(); i < n; ++i){
//            Brick* brick = dynamic_cast<Brick*>(cItems[i]);
//            // collides with brick
//            if (brick){
//                double ballx = ball->pos().x();
//                double bally = ball->pos().y();
//                double brickx = brick->pos().x();
//                double bricky = brick->pos().y();

//                // collides from bottom
//                if (bally >= bricky + brick->getHeight() && ball->y_velocity < 0){
//                    ball->y_velocity = -1 * ball->y_velocity;
//                }

//                // collides from top
//                if (bricky >= bally + ball->rect().height() && ball->y_velocity > 0 ){
//                    ball->y_velocity = -1 * ball->y_velocity;
//                }

//                // collides from right
//                if (ballx >= brickx + brick->getWidth() && ball->x_velocity < 0){
//                    ball->x_velocity = -1 * ball->x_velocity;
//                }

//                // collides from left
//                if (brickx >= ballx + ball->rect().width()  && ball->x_velocity > 0){
//                    ball->x_velocity = -1 * ball->x_velocity;
//                }

//                //emit destroy(brick);

////                brick->setHits(brick->getHits()-1);

////                if(brick->getHits()==1)
////                {
////                    brick->update();
////                }

////                else {
////                    scene->removeItem(brick);
////                    delete brick;
////                }
//            }
//        }

//}
