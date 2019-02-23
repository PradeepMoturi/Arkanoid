#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "start_menu.h"

Game *game;
Paddle *paddle;
startMenu *smenu;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game=new Game();

    //start menu will be started here

    smenu=new startMenu();

    smenu->configure();

    smenu->show();

    return a.exec();
}
