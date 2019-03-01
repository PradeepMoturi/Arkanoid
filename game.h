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
#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>
#include "backgroundmusic.h"
#include "score.h"
#include "ball.h"
#include "gridlayout.h"
#include "powerup.h"
#include "ballworker.h"
#include <vector>
#include "powerup.h"

/*!
 * \brief The Game class
 *
 * Game class creates many connections, creates the grid, handles brick ball collisions, creates new worker threads,
 * new ball objects, starts the timer, updates the brick status, powerup status and many more..
 */

class Game:public QGraphicsView{
Q_OBJECT
public:
    /*!
     * \brief Game
     * \param parent pointer of the game object is set to null
     */
    Game(QWidget *parent=nullptr);
    ~Game();
    QGraphicsScene *scene; /*!<stores the scene of the all the game object.*/
    Score *score; /*!<stores the score object of the game*/

    /*!
     * \brief mainConnections
     * \param worker
     *
     * The ballworker is sent as a parameter to this function. This function handles all
     * the connections for the main ball.
     */
    void mainConnections(ballworker* worker);

    /*!
     * \brief sideConnections
     * \param worker
     *
     * The ballworker is sent as a parameter to this function. This function handles all
     * the connections for the newly created balls, mainly for the timer, worker, paddle and ball
     * objects.
     */
    void sideConnections(ballworker* worker);

    /*!
     * \brief removeConnections
     * \param worker
     *
     * The ballworker is sent as a parameter to this function. This function
     * removes all the connections created in the mainConnections and the sideConnections,
     * mainly for the timer,worker,paddle and ball objects.
     */
    void removeConnections(ballworker* worker);

    /*!
     * \brief powerConnections
     * \param power
     *
     * The Powerup object is sent as a parameter to this functions which handles all the connections
     * for the power object mainly for the power,timer and worker objects.
     */
    void powerConnections(Powerup* power);

    /*!
     * \brief remove_brick
     * \param brick
     *
     * This member function deletes the brick from the scene after receiving it from the brick_collision
     * function.
     */
    void remove_brick(Brick *brick);
signals:
    /*!
     * \brief pausemusic
     *
     * This member function pauses the background music.
     */
    void pausemusic();

    /*!
     * \brief resumemusic
     *
     * This member function resumes the backgroud music.
     */
    void resumemusic();
    void restartmusic();
    void brick_sound();

public slots:
    /*!
     * \brief ballpositionupdater
     * \param b The ball which is passed to be transformed to new co-ordinates.
     * \param x New x co-ordinate of the ball.
     * \param y New y co-ordinate of the ball.
     *
     * This slot updates the position of the ball to the new x and y coordinates taking the signal
     * ballposupdater from the ball worker.
     */
    void ballpositionupdater(Ball*b, double x, double y);

    /*!
     * \brief build
     *
     * This member function initialises music, main ball, ballworker and timer objects and creates a new thread.
     * It moves the ballworker object to the new thread and starts the timer and mainConnections function is
     * called here.
     */
    void build();

    void start();
    void restart();
    void pause();

    /*!
     * \brief end
     *
     * This member function takes worker and ball objects as parameters, removes all the connections
     * deletes the worker objects, displays the end menu when all the ball objects are moved out of
     * the scene. This slot is triggered when it receives the endgame signal from the worker object.
     */
    void end(ballworker*,Ball*);

    /*!
     * \brief removepowerup
     *
     * This member function removes the powerup object from the scene as soon as it receives the destroy_powerup
     * signal from the paddle object. It removes the powerup object from the scene and also deletes the
     * powerup object.
     */
    void removepowerup(Powerup*);

    /*!
     * \brief Multiply_ball
     *
     * This member function doubles every ball object in the ball_list and gives it a opposite direction for
     * the x-velocity, creates a new thread, adds the newly created ball and the worker object to their respective lists.
     * Each of the worker objects is moved to the newly created thread. The newly created items are added to the scene. The
     * connections for each of the newly created ball,worker and timer objects are called by the sideConnections function.This
     * slot is triggered by the multiball signal from the paddle object.
     */
    void Multiply_ball();

    /*!
     * \brief updateStatus
     *
     * This member function updates the fireball status to true and fire_time to zero as soon as it receives the sendStatus
     * signal from the paddle object.
     */
    void updateStatus();

private:
    int fire_time=0; /*!<stores approximately the time the ball objects are in fire mode after picking up the powerup*/
    bool status; /*!stores the status of the fire mode for the ball objects<*/

    /*!
     * \brief brick_collision
     * \param b
     *
     * This member functions takes in the ball object as the parameter and handles all the collisions with the ball,
     * increases the score after collisions, updates the status of the collided bricks, either updating the colour of
     * the ball or removing the brick from the scene and finally updating the velocity of the brick.
     */
    void brick_collision(Ball* b);

    Ball* ball; /*!<stores the pointer to the main ball*/
    std::vector <Ball*> ball_list; /*!<ball_list stores the list of all ball_objects currently safe in the scene*/
    std::vector <ballworker*> worker_list; /*!<worker_list stores the list of all worker_objects in the scene*/
    std::vector<Powerup*> power_list; /*!<power_list stores the list of all the Powerup objects.*/

    /*!
     * \brief setup_scene
     *
     * This member function creates a new QGraphicsScene object, sets the background image on to a fixed
     * scene size, turns off the scrollbar both horizontally and vertically.
     */
    void setup_scene();
    gridlayout* grid;/*!<stores the brick layout in the scene.*/
    QTimer *timer; /*!<timer object*/

    /*!
     * \brief createGrid
     * \param rows
     * \param columns
     *
     * This function takes rows and columns as parameters and creates the grid.
     */
    void createGrid(int rows,int columns);

    BackgroundMusic* music; /*!<object of custom class BackgroundMusic.*/

    std::map<QThread*,int> thread_map;
    std::map<ballworker*, QThread*> balltothread;
};

#endif // GAME_H
