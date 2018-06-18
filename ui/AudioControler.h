#pragma once
#include <QMediaPlayer>
#include <QThread>
#include <QBuffer>
class AudioControler : public QObject
{
public:
    static AudioControler* getInstance();
    ~AudioControler();
public slots:
    void playBGM();
    void playMusic(const QString &path);
private slots:
    void doRepeat(QMediaPlayer::State state);

private:
    bool changing;
    AudioControler();
    QThread * thread;
    QMediaPlayer *player;
};

