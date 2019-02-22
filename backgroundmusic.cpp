#include "backgroundmusic.h"
#include <iostream>
BackgroundMusic::BackgroundMusic()
{
    player = new QMediaPlayer();
    player->setMedia(QUrl("qrc:/data/bgm.mp3"));
    //player->play();
}
void BackgroundMusic::run()
{
    exec();
}
void BackgroundMusic::exec()
{

    while(!QThread::currentThread()->isInterruptionRequested())
    {
        std::cout<<"Her";
        if(player->state()==player->StoppedState)
        {
            player->play();
            std::cout<<"Working";
        }
    }

    player->stop();
    return;
}
BackgroundMusic::~BackgroundMusic()
{
    delete player;
}
