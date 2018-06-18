#include "AudioControler.h"
#include <QFile>


AudioControler::AudioControler()
{
    thread = new QThread;
    thread->start();
    moveToThread(thread);

    player = new QMediaPlayer;
    player->moveToThread(thread);
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
    player->deleteLater();
}

void AudioControler::playBGM()
{
    AudioControler::getInstance()->playMusic("res/bgm.mp3");
}

void AudioControler::playMusic(const QString &path)
{
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}
