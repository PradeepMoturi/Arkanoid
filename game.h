#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "backgroundmusic.h"
class Game:public QGraphicsView{
public:
    Game(QWidget *parent=NULL);
    ~Game();
    QGraphicsScene *scene;
    void start();
private:
    BackgroundMusic* music;
};

#endif // GAME_H
