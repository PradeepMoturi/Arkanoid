#include "gridlayout.h"
#include <QtMath>

gridlayout::gridlayout(int rows, int columns, QGraphicsScene* ptr)
{
    scene = ptr;
    Build_Grid(rows,columns);

}

void gridlayout::Build_Grid(int rows, int columns)
{
    //create grid of size m and n
     double start_x=110;
     double start_y=150;
     double temp_x;
     double temp_y;
     double bheight=20;
     double bwidth=80;

     for(int i=0;i<rows;i++)
     {
         int hits=1;
         temp_x=start_x;
         temp_y=start_y;

         for(int j=0;j<columns;j++)
         {
             if(i==0||j==0||j==(columns-1)) hits=2;
             else hits=1;

             if(i==rows-1)
             {
                 Brick *brick=new Brick(1,hits); //0123
                 brick->setPos(temp_x,temp_y);
                 scene->addItem(brick);
             }

             else {
                 Brick *brick=new Brick(0,hits); //0123
                 brick->setPos(temp_x,temp_y);
                 scene->addItem(brick);
             }

             temp_x+=bwidth;
         }

         start_y+=bheight;
     }
}

