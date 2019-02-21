#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Game:public QGraphicsView{
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;
    void start();
};


#endif // GAME_H
