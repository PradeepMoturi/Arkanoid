#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
class Game:public QGraphicsView{
Q_OBJECT
public:
    Game(QWidget *parent=nullptr);
    QGraphicsScene *scene;
public slots:
    void build();
    void restart();
    void end();
signals:
    void stop();
    void start();
private:
    QTimer *timer = nullptr;
    void keyPressEvent(QKeyEvent *event);
};


#endif // GAME_H
