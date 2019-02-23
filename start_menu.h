#ifndef MENU_H
#define MENU_H

#include <QGraphicsView>
#include <QPushButton>

class startMenu:public QGraphicsView
{
    public:
    startMenu(QWidget *parent=nullptr);
    QGraphicsScene *scene;
    QPushButton *play;
    QPushButton *exit;
    public slots:
    void configure();
};

#endif // MENU_H
