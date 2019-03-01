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
#ifndef BALLWORKER_H
#define BALLWORKER_H
#include <QThread>
#include <QObject>
#include <QGraphicsScene>
#include "ball.h"
#include "brick.h"

/*!
 * \brief The ballworker class Inherits from QObject
 *
 * ballworker contains a ball and this object does all the work for the ball.
 * It handles the Paddle Collision for the ball and also the brick collision.
 */
class ballworker : public QObject
{
    Q_OBJECT

public:

    /*!
     * \brief ballworker Constructor
     * \param curr Current Scene of the Ball
     * \param new_ball Pointer to a ball object
     *
     * Sets the Width and height of the screen
     */
    ballworker(QGraphicsScene* curr,Ball *new_ball);

    /*!
     * \brief ball ball for which this class does work for.
     */
    Ball* ball;

private:

    /*!
     * \brief screen_width Contains the Width of the screen.
     */
    double screen_width;

    /*!
     * \brief screen_height Contains the Height of the screen
     */
    double screen_height;

    /*!
     * \brief wall_collision Member Function to check for wall collision and update the velocity of the Ball.
     */
    void wall_collision();

public slots:

    /*!
     * \brief ball_move moves the ball
     *
     * It is a Slot to move the ball. It is connected to timeout signal of the timer in the Game. This slot is called by main theread every 5ms.
     */
    void ball_move();

    /*!
     * \brief PaddleCollisionDetected Paddle Collision has been detected
     * \param nball this slot changes the direction of nball
     * \param left_corner left_corner is true if the it crosses left side of paddle.
     * \param right_corner right_corner is true if the ball crosses right side of paddle.
     *
     *  It is connected to timeout() signal of the timer in Game i.e main thread
     *  If both left_corner and right_corner are false we reverse the y velocity of the ball else we change the x or y velocity respectively
     */
    void PaddleCollisionDetected(Ball* nball,bool left_corner,bool right_corner);

signals:

    /*!
     * \brief ballposupdater Signal to change the position of the ball
     * \param nball Pointer to the ball
     * \param x New x position of the ball
     * \param y New y position of the ball
     *
     * This signal is conected to a slot ballpositionupdater in Game i.e Main Thread.
     * Sends the new position of the ball.
     */
    void ballposupdater(Ball* nball,double x, double y);

    /*!
     * \brief endgame Signal is raised when the ball crosses bottom surface
     * \param nball
     *
     * This Signal is connected to a slot in end in Game i.e Main Thread.
     */
    void endgame(ballworker*,Ball* nball);

};
#endif // BALLWORKER_H
