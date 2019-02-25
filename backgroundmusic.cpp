#include "backgroundmusic.h"

BackgroundMusic::BackgroundMusic()
{
    player = new QMediaPlayer();
    player->setMedia(QUrl("qrc:/data/bgm.mp3"));
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
BackgroundMusic::~BackgroundMusic()
{
    delete player;
}
