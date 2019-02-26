#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "backgroundmusic.h"
#include "ball.h"
#include "gridlayout.h"
#include "ballworker.h"
#include <vector>
class Game:public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget *parent=nullptr);
//    Game(QWidget *parent=NULL);
    ~Game();
    QGraphicsScene *scene;

public slots:
    void ballpositionupdater(double x, double y);
    void build();
    void restart();
    void end();
    void pause();
    void remove_brick(Brick *brick);
signals:
    void start();
private:
    void brick_collision();
    Ball* ball;
    std::vector <Ball*> ball_list;
    std::vector <ballworker*> worker_list;
    void setup_scene();
    gridlayout* grid;
//    QTimer *timer = nullptr;
//    void keyPressEvent(QKeyEvent *event);
    void createGrid(int rows,int columns);
    BackgroundMusic* music;
};

#endif // GAME_H
