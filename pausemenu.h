#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QMainWindow>
#include "button.h"
/*!
 * \brief The PauseMenu class
 *
 * The Pause Menu class is used to display the pause menu whenever esc is pressed.
 * It contains three options - "Resume", "Restart" and "Exit".
 */
class PauseMenu : public QMainWindow
{
Q_OBJECT
public:
    /*!
     * \brief PauseMenu
     * \param parent
     *
     * It is Constructor of the class PauseMenu.
     */
    PauseMenu(QWidget *parent = nullptr);
private slots:
    /*!
     * \brief handleRestart
     *
     * Starts the game from the begining.
     */
    void handleRestart();

    /*!
     * \brief handleEndGame
     *
     * Exits out of the game.
     */
    void handleEndGame();

    /*!
     * \brief handleResume
     *
     * Continues game from the paused point.
     */
    void handleResume();
private:
    /*!
     * \brief m_restart
     *
     * It is Restart button.
     */
    CustomButton* m_restart;

    /*!
     * \brief m_exitGame
     *
     * It is Exit button.
     */
    CustomButton* m_exitGame;

    /*!
     * \brief m_resume
     *
     * It is Resume button.
     */

    CustomButton* m_resume;

};

#endif // PAUSEMENU_H
