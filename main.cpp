#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "start_menu.h"
#include "start_menu.h"
Game *game;
Paddle *paddle;
start_menu *smenu;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game=new Game();

    //start menu will be started here

    smenu=new start_menu();

    smenu->show();

    return a.exec();
}
