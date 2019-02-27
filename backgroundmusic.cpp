#include "backgroundmusic.h"

BackgroundMusic::BackgroundMusic()
{
    player = new QMediaPlayer();
    player->setMedia(QUrl("qrc:/Sound/data/bgm.mp3"));
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
BackgroundMusic::~BackgroundMusic()
{
    delete player;
}
