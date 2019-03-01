#ifndef ENDMENU_H
#define ENDMENU_H

#include <QMainWindow>
#include "startpage.h"
/*!
 * \brief The End Menu class
 *
 * This is displayed when you loose.
 */
class EndMenu : public QMainWindow
{
Q_OBJECT

public:
    /*!
     * \brief Constructor for the End Menu.
     * \param parent
     *
     * This adds background, buttons and connections.
     */
    EndMenu(QWidget *parent = nullptr);

private slots:
    /*!
     * \brief Fucntion run when Restart is clicked.
     *
     * This sends restart signal to Game.
     */
    void handleRestart();
    /*!
     * \brief Function to run when End Game is clicked.
     *
     * This exits the Game safely.
     */
    void handleEndGame();

private:
    /*!
     * \brief Restart Button.
     *
     * This is a QPushButton item for restart option.
     */
    CustomButton* m_restart;
    /*!
     * \brief Exit Game Button.
     *
     * This is a QPushButton item for Exit game.
     */
    CustomButton* m_exitGame;
};

#endif // ENDMENU_H
