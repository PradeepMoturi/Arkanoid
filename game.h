#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "backgroundmusic.h"
#include "score.h"

class Game:public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget *parent=nullptr);
//    Game(QWidget *parent=NULL);
    ~Game();
    QGraphicsScene *scene;
    Score *score;
public slots:
    void build();
    void restart();
    void end();
    void pause();
signals:
    void start();
private:
//    QTimer *timer = nullptr;
//    void keyPressEvent(QKeyEvent *event);
    void createGrid(int rows,int columns);
    BackgroundMusic* music;
};

#endif // GAME_H
