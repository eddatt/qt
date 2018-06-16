#pragma once
#include <QString>
#include <QPixmap>
#include <QSize>
namespace UIUtility {
    QPixmap getPixmap(const QString &type, const QString &name, const QSize &size = QSize(), bool white_and_black = false);
    const QFont &getDefaultFont();
    const QFont &getInfoBarnerFont();
    const QFont &getMarkNumberFont();

    const QRectF getGraphicsSceneRect();

    QString getBackgroundPath(const QString &scene);

}

