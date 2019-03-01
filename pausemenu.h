#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QMainWindow>
#include "button.h"

class PauseMenu : public QMainWindow
{
Q_OBJECT
public:
    PauseMenu(QWidget *parent = nullptr);
private slots:
    void handleRestart();
    void handleEndGame();
    void handleResume();
private:
    CustomButton* m_restart;
    CustomButton* m_exitGame;
    CustomButton* m_resume;

};

#endif // PAUSEMENU_H
