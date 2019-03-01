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
#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

/*!
 * \brief The Powerup class
 *
 * This class creates a new Powerup class, sets the position and movement of
 * the object to the scene.
 */

class Powerup:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:

    /*!
     * \brief Powerup
     * \param parent parent pointer is set to nullptr
     *
     * This constructor sets the velocity of the powerup, sets the dimensions of the powerup object
     * brushes it in green.
     */
    Powerup(QGraphicsItem* parent = nullptr);

    /*!
     * \brief set
     * \param id
     * \param x
     * \param y
     *
     * This member function sets up the id, x and y as co-ordinates for the powerup.
     */
    void set(int id, double x, double y);
    int powerup_id; /*!<stores the powerup id*/

    /*!
     * \brief getwidth
     * \return returns the width of the paddle.
     */
    double getwidth();

    /*!
     * \brief getheight
     * \return returns the height of the paddle.
     */
    double getheight();
private:
    double x_velocity; /*!<stores the x direction velocity */
    double y_velocity; /*!<stores the y direction velocity*/
    double powerup_width;/*!<stores the powerup width*/
    double powerup_height; /*!<stores the powerup height*/
signals:
    /*!
     * \brief remove_connection
     *
     * This signal sends a signal remove_connection to trigger the removal of powerup.
     */
    void remove_connection(Powerup*);
public slots:
    /*!
     * \brief powerup_move
     *
     * This slot is triggered when it takes the timer timerout signal and it moves down
     * the powerup.
     */
    void powerup_move();
};

#endif // POWERUP_H
