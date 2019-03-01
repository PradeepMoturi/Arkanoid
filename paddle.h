/*
Copyright (c) 2019 Revanth Babu, Pradeep Moturi, Jeevan Chandra, Udit Maniyar

This file is part of Arkanoid 
(see https://github.com/IITH-SBJoshi/concurrency-1).

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QObject>
#include "ball.h"
#include"powerup.h"
/*!
 * \brief The Paddle class
 *
 * This class is used to create a paddle object in the game.
 */
class Paddle:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    /*!
     * \brief Paddle constructor
     * \param parent The parent pointer to the paddle object is set to null.
     *
     * This constructor is used to create a paddle of type QGraphicsRectItem with a default paddle width
     * and height and sets the paddle position position to the bottom center of the window with the colour
     * filled as blue. It also starts the timer to note the keypress events.
     */
    Paddle(QGraphicsItem *parent=nullptr);

    /*!
     * \brief keyPressEvent
     * \param event The event is default parameter sent for the builtin member function
     *
     * This event handler, for event event receives key press events for the widget.
     */
    void keyPressEvent(QKeyEvent *event);

    /*!
     * \brief keyReleaseEvent
     * \param event The event is default parameter sent for the builtin member function
     *
     * This event handler, for event event releases/deactivates the key press events for the widget.
     */
    void keyReleaseEvent(QKeyEvent* event);

    /*!
     * \brief move_paddle
     * \param x stores the distance to be displaced by.
     *
     * This function sets the position by displacing it by a distance x.
     */
    void move_paddle(double x);

    /*!
     * \brief height
     * \return returns the height of the paddle.
     */
    qreal height();

    /*!
     * \brief width
     * \return returns the width of the paddle.
     */
    qreal width();

    /*!
     * \brief getCenterX
     * \return returns the center x co-ordinate of the paddle.
     */
    double getCenterX();

    /*!
     * \brief rightCornerX
     * \return returns the right corner x co-ordinate of the paddle.
     */
    double rightCornerX();

    /*!
     * \brief leftCornerX
     * \return returns the left corner x co-ordinate of the paddle.
     */
    double leftCornerX();

    /*!
     * \brief timerEvent
     *
     * The timerEvent built-in function activates the position of the paddle at every timeout of the timer.
     * It also activates the CollisionChecker function everytime and it also resets the paddle width of the
     * powered up expanded paddle to normal after cnt reaches a certain value. The same holds to reset the paddle
     * width from the compressed paddle to normal width after cnt reaches a certain value.
     */
    void timerEvent(QTimerEvent *);

    /*!
     * \brief CollisionChecker
     *
     * This function checks for the list of colliding items be it an ball type or powerup type.
     * It emits the ballCollision signal if the object to be collided is Ball type and it also
     * handles the powerup of four types accordingly emitting respective signals and destroys the
     * powerup object collided.
     */
    void CollisionChecker();

signals:
    /*!
     * \brief multiballadd
     *
     * Signal raised to add multiballs to the scene.
     */
    void multiballadd();

    /*!
     * \brief sendStatus
     *
     * Signal raised to set the fireball status to true.
     */
    void sendStatus();

    /*!
     * \brief destroy_powerup
     *
     * Signal raised to destroy the powerup after it collides with the paddle.
     */
    void destroy_powerup(Powerup *);

    /*!
     * \brief stop
     *
     * Signal raised to pause the game and display another window.
     */
    void stop();
    /*!
     * \brief ball
     * \param ball
     * \param left_corner
     * \param right_corner
     *
     *
     * Collision Signal raised that a ball collision with the paddle occured.
     */
    void ballCollision(Ball* ball,bool left_corner,bool right_corner);
private:
    int cnt; /*!<stores the number of times a timeout signal triggered after taking the paddle size powerup.*/
    double paddle_height; /*!<stores the height of the paddle.*/
    double paddle_width; /*!<stores the width of the paddle.*/
    QGraphicsScene *scene; /*!<stores the scene of the paddle.*/
    QMap<int,bool> keys; /*!<stores the information of keyPress event.*/
};

#endif // PADDLE_H
