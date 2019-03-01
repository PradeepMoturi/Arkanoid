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
#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include "brick.h"
#include <QGraphicsScene>

/*!
 * \brief The gridlayout class
 *
 * This class creates a grid of bricks in the scene
 */

class gridlayout
{
public:
    /*!
     * \brief gridlayout
     *
     * This constructor takes in the scene and level of the game as input.
     * \param curr stores the current scene where this grid needs to be placed.
     * \param level refers to the level id that needs to be mapped from the text file.
     */
    gridlayout(QGraphicsScene* curr,int level);

    int bricks_remaining = 0;
private:

    /*!
     * \brief scene
     *
     * scene holds the variable
     */
    QGraphicsScene* scene;
    /*!
     * \brief Build_Grid
     *
     * This function takes in the level as the input and displays the grid in the scene.
     * \param level
     */
    void Build_Grid(int level);
};
#endif // GRIDLAYOUT_H
