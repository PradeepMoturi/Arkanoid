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
#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>
#include <QGraphicsView>
#include <QThread>
#include <QMutex>

/*!
 * \brief The Ball class
 *
 * Inherits from QObject and QGraphicsEllipse
 * Contains all the information related to ball such as x direction velocity, y direction velocity, current position in the scene
 */
class Ball:public QObject,public QGraphicsEllipseItem
{

    Q_OBJECT

public:
    /*!
     * \brief Ball Constructor
     * \param parent is always set to null
     *
     * Ball radius is initialised to 20 .
     * X and Y velocities are set to -1/5 pix/secs, -2/5 pix/secs respectively
     * Color of Ball is set to Red
     * Intial Position of Ball is set to the middle of paddle
     */
    Ball(QGraphicsItem *parent=nullptr);

    /*!
     * \brief radius
     * \return Radius of the Ball
     */
    double radius();

    /*!
     * \brief getCenterX
     * \return X Coordinate of the center of the Ball
     */
    double getCenterX();

    /*!
     * \brief get_xvelocity
     * \return Velocity of the Ball in X Direction
     */
    double get_xvelocity();

    /*!
     * \brief get_yvelocity
     * \return Velocity of the Ball in Y Direction
     */
    double get_yvelocity();

    /*!
     * \brief set_xvelocity
     * \param pos Carries Information regarding how to change in the velocity of the ball
     *
     * If Boolean pos is true then X directional velocity is made positive
     * If Boolean pos is false then X directional velocity is made negative.
     * Since this a critical section mutex lock is used to make it strictly serial
     */
    void set_xvelocity(bool pos);

    /*!
     * \brief set_yvelocity
     * * \param pos Carries Information regarding how to change in the velocity of the ball
     *
     * If Boolean pos is true then Y directional velocity is made positive
     * If Boolean pos is false then Y directional velocity is made negative.
     * Since this a critical section mutex lock is used to make it strictly serial
     */
    void set_yvelocity(bool pos);

    /*!
     * \brief set_xnewvelocity Sets new given x velocity
     * \param newvelx input xvelocity to be set
     *
     */
    void set_xnewvelocity(double newvelx);
private:
    /*!
     * \brief mutex QMutex Object Used to lock the velocity of ball.
     */
    QMutex mutex;

    /*!
     * \brief ball_radius Stores the radius of ball
     */
    double ball_radius;

    /*!
     * \brief x_velocity Stores the velocity of the ball in x direction
     */
    double x_velocity;

    /*!
     * \brief y_velocity Stores the velocity of the ball in y direction
     */
    double y_velocity;
};

#endif // BALL_H
