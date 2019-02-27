#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "backgroundmusic.h"
#include "score.h"
#include "ball.h"
#include "gridlayout.h"
#include "powerup.h"
#include "ballworker.h"
#include <vector>
#include "powerup.h"

class Game:public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget *parent=nullptr);
    ~Game();
    QGraphicsScene *scene;
    Score *score;
    void mainConnections(ballworker* worker);
    void sideConnections(ballworker* worker);
    void removeConnections(ballworker* worker);
    void powerConnections(Powerup* power);

public slots:
    void ballpositionupdater(Ball*b, double x, double y);
    void build();
    void start();
    void restart();
    void end(ballworker*,Ball*);
    void pause();
    void remove_brick(Brick *brick);
    void removepowerup(Powerup*);
    void Multiply_ball(Powerup*);
private:
    void brick_collision(Ball* b);
    Ball* ball;
    std::vector <Ball*> ball_list;
    std::vector <ballworker*> worker_list;
    std::vector<Powerup*> power_list;
    void setup_scene();
    gridlayout* grid;
    QTimer *timer;
    void createGrid(int rows,int columns);
    BackgroundMusic* music;
};

#endif // GAME_H
