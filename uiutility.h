#pragma once
#include <QString>
#include <QPixmap>
#include <QSize>

namespace UIUtility {
    QPixmap getPixmap(const QString &type, const QString &name, const QSize &size = QSize());
    const QFont &getDefaultFont();

    QString getBackgroundPath(const QString &scene);
};



