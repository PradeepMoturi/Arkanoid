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
#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

/*!
 * \brief The Score class
 *
 *It is used to computing the Score in the game.
 */
class Score: public QGraphicsTextItem
{
public:
    /*!
     * \brief Score
     * \param parent
     *
     * It is the constructor of the Score class.
     */
    Score(QGraphicsItem * parent = nullptr);

    /*!
     * \brief increase
     *
     * It increases the score by 1 when ball hits a brick.
     */
    void increase();

    /*!
     * \brief getscore
     * \return
     *
     * It returns the Score in the integer format.
     */
    int getscore();
private:
    /*!
     * \brief score
     *
     * This variable stores the Score.
     */
    int score;
};

#endif // SCORE_H
