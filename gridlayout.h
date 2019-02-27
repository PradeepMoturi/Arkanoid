#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include "brick.h"
#include <QGraphicsScene>
class gridlayout
{
public:
    gridlayout(QGraphicsScene* curr,int level);

private:
    QGraphicsScene* scene;
    void Build_Grid(int level);
};
#endif // GRIDLAYOUT_H
