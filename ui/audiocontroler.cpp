#include "AudioControler.h"
#include <QFile>


AudioControler::AudioControler()
{
    changing = false;
    thread = new QThread;
    thread->start();
    moveToThread(thread);

    player = new QMediaPlayer;
    player->moveToThread(thread);
    connect(player, &QMediaPlayer::stateChanged, this, &AudioControler::doRepeat);
}


AudioControler* AudioControler::getInstance()
{
    static AudioControler audio;
    return &audio;
}

AudioControler::~AudioControler()
{
    thread->terminate();
    thread->deleteLater();
    changing = true;
    player->stop();
    player->deleteLater();
}

void AudioControler::playBGM()
{
    AudioControler::getInstance()->playMusic("res/bgm.mp3");
}

void AudioControler::playMusic(const QString &path)
{
    changing = true;
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
    changing = false;
}

void AudioControler::doRepeat(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState && !changing) {
        player->play();
    }
}
