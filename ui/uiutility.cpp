#include "uiutility.h"

#include <QFile>
#include <QFont>
#include <QImage>
#include <QMessageBox>

QPixmap UIUtility::getPixmap(const QString &type, const QString &name, const QSize &size, bool white_and_black)
{
    QString path = QString("res/%1/%2.png").arg(type).arg(name);
    if (QFile::exists(path)) {

        if (white_and_black) {
            QImage img(path);
            for (int i = 0; i < img.width(); i++) {
                for (int j = 0; j < img.height(); j++) {
                    QRgb pixel = img.pixel(i, j);
                    int gray = qGray(pixel);
                    QRgb grayPixel = qRgb(gray, gray, gray);
                    img.setPixel(i, j, grayPixel);
                }
            }
            return QPixmap::fromImage(img).scaled(size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);    
        }
        else {
            QPixmap px(path, nullptr);
            if (!size.isEmpty()) {
                return px.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            }
            else {
                return px;
            }
        }
        

    }
    else {
        QMessageBox::warning(nullptr, "image not found", QString("Can not find the Image %1").arg(path));
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


const QFont & UIUtility::getMarkNumberFont()
{
    static QFont f = QFont("Microsoft YaHei", 8);
    return f;
}

const QRectF UIUtility::getGraphicsSceneRect()
{
    return QRectF(0, 0, 1280, 768);
}

QString UIUtility::getBackgroundPath(const QString &scene)
{
    if (scene == "start") {
        return "res/bg.jpg";
    }
    else if (scene == "on_game")
        return "res/start.jpg";
    else {
        return "";
    }
}
