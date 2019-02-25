#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include "brick.h"
#include <QGraphicsScene>
class gridlayout
{
public:
    gridlayout(int rows,int columns,QGraphicsScene* view);

private:
    QGraphicsScene* scene;
    void Build_Grid(int rows, int columns);

};
#endif // GRIDLAYOUT_H
