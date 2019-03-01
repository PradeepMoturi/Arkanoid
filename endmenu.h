#ifndef ENDMENU_H
#define ENDMENU_H

#include <QMainWindow>
#include "startpage.h"

class EndMenu : public QMainWindow
{
Q_OBJECT

public:
    EndMenu(QWidget *parent = nullptr);
    void display();

private slots:
    void handleRestart();
    void handleEndGame();

private:
    CustomButton* m_restart;
    CustomButton* m_exitGame;
};

#endif // ENDMENU_H
