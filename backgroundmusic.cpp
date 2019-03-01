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
#include "backgroundmusic.h"

BackgroundMusic::BackgroundMusic()
{
    player = new QMediaPlayer();
    player->setMedia(QUrl("qrc:/Sound/data/Sounds/bgm.mp3"));

    brickNoise = new QMediaPlayer();
    brickNoise->setMedia(QUrl("qrc:/Sound/data/Sounds/brickNoise.mp3"));
    brickNoise->setVolume(15);
}
void BackgroundMusic::run()
{
    exec();
}
void BackgroundMusic::exec()
{

    while(!QThread::currentThread()->isInterruptionRequested())
    {
        if(player->state()==player->StoppedState)
        {
            player->play();
        }
    }

    player->stop();
    return;
}
void BackgroundMusic::pausemusic()
{
    player->pause();
}
void BackgroundMusic::resumemusic()
{
    player->play();
}

void BackgroundMusic::restartmusic()
{
    player->stop();
    player->play();
}
BackgroundMusic::~BackgroundMusic()
{
    delete player;
}

void BackgroundMusic::Brick_Sound()
{
    brickNoise->play();
}
