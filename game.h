#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Game:public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget *parent=nullptr);
    QGraphicsScene *scene;
    //void keyPressEvent(QKeyEvent *event);
public slots:
    void start();
};


#endif // GAME_H
