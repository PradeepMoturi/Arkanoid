#ifndef GRID_H
#define GRID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

class Brick:public QGraphicsItem
{
public:
    Brick(int id,int cnt,QGraphicsItem *parent=nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getHits();
    int getHeight();
    int getWidth();
    void decHits();
    void setHeight(int x);
    void setWidth(int x);
    int brick_id;

private:
    int hits;
    int height;
    int width;
};

#endif // GRID_H
