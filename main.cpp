#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "game.h"
#include "ball.h"
#include "paddle.h"

Game *game;
Paddle *paddle;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game=new Game();
    game->show();
    game->start();

    return a.exec();
}
