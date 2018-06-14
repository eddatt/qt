#include "uiutility.h"

#include<QFile>
#include <QFont>

QPixmap UIUtility::getPixmap(const QString &type, const QString &name, const QSize &size)
{
    QString path = QString("res/%1/%2.png").arg(type).arg(name);
    if (QFile::exists(path)) {
        QPixmap px(path);
        if (!size.isEmpty()) {
            return px.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        else {
            return px;
        }

    }
    else {

    }
    return QPixmap();
}

const QFont & UIUtility::getDefaultFont()
{
    static QFont f = QFont("Microsoft YaHei", 20);
    return f;
}

const QFont & UIUtility::getInfoBarnerFont()
{
    static QFont f = QFont("Microsoft YaHei", 14);
    return f;
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
