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
#ifndef BACKGROUNDMUSIC_H
#define BACKGROUNDMUSIC_H
#include <QMediaPlayer>
#include <QThread>
#include <QObject>
/*!
 * \brief The BackgroundMusic class
 * Inherits from QThread.
 * Used to play Background music and sounds whenever ball hits paddle and bricks
 */
class BackgroundMusic : public QThread
{
    Q_OBJECT
public:
    // member functions
     /**
      * \brief Constructor
      *
      * Construct a new media player
      */
    BackgroundMusic();

    /**
     * \brief run Starting point of the thread
     *
     * The starting point for the thread. After calling start(), the newly created thread calls this function.
     * Returning from this method will end the execution of the thread.
     * Executes the exec() member function.
     */

    void run();


    /*!
     * \brief exec
     *
     * Runs in a loop and restarts song if finished
     */
    void exec();

    /*!
      * \brief Destructor
      *
      * removes the player which was started in constructor
      */
    ~BackgroundMusic();

public slots:
    /*!
     * \brief pausemusic Pauses the music player
     */
    void pausemusic();

    /*!
     * \brief resumemusic Resumes the music player
     */
    void resumemusic();
    void restartmusic();
    void Brick_Sound();

private:

    /*!
     * \brief player QMediaPlayer object used to play music
     */
    QMediaPlayer* player;
    QMediaPlayer* brickNoise;
};


#endif // BACKGROUNDMUSIC_H
