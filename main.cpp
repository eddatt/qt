#include "BlueMoon.h"
#include <QtWidgets/QApplication>
#include<QGraphicsView>
#include "AudioControler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlueMoon *w = BlueMoon::getInstance();
    w->show();
    AudioControler::getInstance()->playBGM();
    return a.exec();
}
