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
    Brick(int cnt,QGraphicsItem *parent=nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int hits;
};

#endif // GRID_H
