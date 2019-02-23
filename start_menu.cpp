#include "start_menu.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QApplication>
#include "game.h"

extern Game* game;

startMenu::startMenu(QWidget *parent):QGraphicsView(parent)
{
    scene=new QGraphicsScene(0,0,700,700,this);
    setScene(scene);
    setFixedSize(700, 700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void startMenu::configure()
{
    //add the custom button
    play=new QPushButton(nullptr);
    play->setText("Play");
    play->setFixedSize(150,100);
    play->setGeometry(game->width()/2-150,200,150,100);
    exit=new QPushButton(nullptr);
    exit->setText("Exit");
    exit->setFixedSize(150,100);
    exit->setGeometry(game->width()/2,200,150,100);
    scene->addWidget(play);
    scene->addWidget(exit);
    connect(play,SIGNAL(pressed()),game,SLOT(start()));
    connect(exit,SIGNAL(pressed()),qApp,SLOT(quit()));
}
