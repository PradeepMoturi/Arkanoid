#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "backgroundmusic.h"
#include "gridlayout.h"

class Game:public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget *parent=nullptr);
//    Game(QWidget *parent=NULL);
    ~Game();
    QGraphicsScene *scene;

public slots:
    void build();
    void restart();
    void end();
    void pause();
signals:
    void start();
private:
    void setup_scene();
    gridlayout* grid;
//    QTimer *timer = nullptr;
//    void keyPressEvent(QKeyEvent *event);
    void createGrid(int rows,int columns);
    BackgroundMusic* music;
};

#endif // GAME_H
