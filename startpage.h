#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include "button.h"

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void display();

private slots:
    void handleNewGame();
    void handleExitGame();

private:
    CustomButton* m_instructions;
    CustomButton* m_new_game;
    CustomButton* m_enter_game;
    CustomButton* m_exitGame;
};

#endif // STARTPAGE_H
