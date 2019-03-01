/*
Copyright (c) 2019 Revanth Babu, Pradeep Moturi, Jeevan Chandra, Udit Maniyar

This file is part of Arkanoid 
(see https://github.com/IITH-SBJoshi/concurrency-1).

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "gridlayout.h"
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include <QDebug>
gridlayout::gridlayout(QGraphicsScene* curr,int level)
{
    scene = curr;
    bricks_remaining = 0;

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
            bricks_remaining++;
        }
        myFile.close();
        qDebug()<<bricks_remaining;
    }
}

