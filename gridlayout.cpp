#include "gridlayout.h"
#include <QtMath>
#include <QFile>
#include <QTextStream>

gridlayout::gridlayout(QGraphicsScene* curr,int level)
{
    scene = curr;
    Build_Grid(level);
}

void gridlayout::Build_Grid(int level)
{

    QString file;
    if(level == 1)
    {
        file = ":/Sound/data/level1.txt";
    }
    if(level == 2)
    {
        file = ":/Sound/data/level2.txt";
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
}

