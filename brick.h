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
#ifndef GRID_H
#define GRID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
/*!
 * \brief The Brick class
 * Inherits from QGraphicsItem
 * Stores the information about the brick.
 */

class Brick:public QGraphicsItem
{

public:
    /*!
     * \brief Brick Constructor
     * \param id Tells if the Brick has a Powerup or not
     * \param cnt Gives Information about how many hits are required for the brick to break
     * \param parent Is always set to nullptr
     */
    Brick(int id,int cnt,QGraphicsItem *parent=nullptr);

    /*!
     * \brief boundingRect
     * \return QRectF Object is returned
     */
    QRectF boundingRect() const;

    /*!
     * \brief paint Paints the Bricks
     * \param painter QPainter Object used to paint the brick
     *
     * If the Number of hits is 1 then the the color of Brick is Yellow
     * If the Number of hits is 2 then the the color of Brick is Red
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    /*!
     * \brief getHits
     * \return Number of Hits remaining to break the brick
     */
    int getHits();

    /*!
     * \brief getHeight
     * \return Height of the Brick
     */
    int getHeight();

    /*!
     * \brief getWidth
     * \return Width of the Brick
     */
    int getWidth();

    /*!
     * \brief decHits
     *
     * Reduces the number of hits by 1
     */
    void decHits();

    /*!
     * \brief setHeight
     * \param new_height New Height of the Brick
     *
     * Changes the Height of the Brick
     */
    void setHeight(int new_height);

    /*!
     * \brief setWidth
     * \param new_width New Width of the Brick
     *
     * Changes the Width of the Brick
     */
    void setWidth(int new_width);


    /*!
     * \brief brick_id Contains the Information About the Powerup.
     *
     * No Power up brick_id is 0.
     * Power up : Multiple Ball Power up brick_id is is 1.
     * Power up : Increase in Paddle Length brick_id is 2.
     * Power up : Decrease in Paddle Length brick_id is 3.
     * Power up : Fire Ball brick_id is 4.
     */
    int brick_id;

private:
    /*!
     * \brief hits Stores the number of Hits required to Break the Ball
     */
    int hits;

    /*!
     * \brief height Stores the Height of the Ball
     */
    int height;

    /*!
     * \brief width Stores the Width of the Ball
     */
    int width;
};

#endif // GRID_H
