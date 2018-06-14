#include "uiutility.h"

#include<QFile>

QPixmap UIUtility::getPixmap(const QString &type, const QString &name, const QSize &size)
{
    QString path = QString("res/%1/%2.png").arg(type).arg(name);
    if (QFile::exists(path)) {
        QPixmap pix(path);
        if(size != QSize)
            return pix.scaled(size,Qt::IgnoreAspectRatio)
    }
    else {

    }
    return QPixmap();
}

QString UIUtility::getBackgroundPath(const QString &scene)
{
    if (scene == "start") {
        return "res/bg.jpg";
    }
    else {
        return "";
    }
}
