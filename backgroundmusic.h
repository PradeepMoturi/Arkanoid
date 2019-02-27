#ifndef BACKGROUNDMUSIC_H
#define BACKGROUNDMUSIC_H
#include <QMediaPlayer>
#include <QThread>
#include <QObject>
class BackgroundMusic : public QThread
{
    Q_OBJECT
public:
    BackgroundMusic();
    void run();
    void exec();
    ~BackgroundMusic();
public slots:
    void pausemusic();
    void resumemusic();


private:
    QMediaPlayer* player;
};


#endif // BACKGROUNDMUSIC_H
