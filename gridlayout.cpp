#include "gridlayout.h"
#include <QtMath>
#include <QFile>
#include <QTextStream>

gridlayout::gridlayout(int level, QGraphicsScene* ptr)
{
    scene = ptr;
    Build_Grid(level);

}

void gridlayout::Build_Grid(int level)
{

    QString file;
    if(level == 1)
    {
        file = ":/data/level1.txt";
    }
    if(level == 2)
    {
        file = ":/data/level2.txt";
    }
    QFile myFile(file);
    if (myFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&myFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList point = line.split(" ");
            Brick *brick=new Brick(point[0].toInt(),point[1].toInt());
            brick->setPos(point[2].toDouble(),point[3].toDouble());
            scene->addItem(brick);
        }
    myFile.close();
    }
  
//    //create grid of size m and n
//     double start_x=110;
//     double start_y=150;
//     double temp_x;
//     double temp_y;
//     double bheight=20;
//     double bwidth=80;

//     for(int i=0;i<rows;i++)
//     {
//         int hits=1;
//         temp_x=start_x;
//         temp_y=start_y;

//         for(int j=0;j<columns;j++)
//         {
//             if(i==0||i==(rows-1)||j==0||j==(columns-1)) hits=2;
//             else hits=1;

//             Brick *brick=new Brick(hits);
//             brick->setPos(temp_x,temp_y);

//             scene->addItem(brick);
//             temp_x+=bwidth;
//         }

//         start_y+=bheight;
//     }
}

