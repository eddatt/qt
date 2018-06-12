#include "BlueMoon.h"
#include <QtWidgets/QApplication>
#include<QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlueMoon w(nullptr);
    w.show();
    return a.exec();
}
