#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include "button.h"
/*!
 * \brief The Start Page class.
 *
 * This is the first page you see.
 */
class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    /*!
     * \brief Constructor for the Start page.
     * \param parent
     *
     * This adds background,instructions and buttons.
     */
    MainWindow(QWidget *parent = nullptr);

private slots:
    /*!
     * \brief Function to run when New Game is clicked.
     *
     * This sends the signal to build the game.
     */
    void handleNewGame();
    /*!
     * \brief Function to run when Exit Game is clicked.
     *
     * This safely exits the game.
     */
    void handleExitGame();

private:
    /*!
     * \brief New Game button.
     *
     * This is a QPushButton object for New Game button.
     */
    CustomButton* m_new_game;
    /*!
     * \brief Exit Game button
     *
     * This is a QPushButton object for Exit Game button.
     */
    CustomButton* m_exitGame;
};

#endif // STARTPAGE_H
