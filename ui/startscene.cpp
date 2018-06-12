#include "startscene.h"
#include <QFile>
#include <QPainter>
#include <QPixmap>
#include <QtDebug>

StartScene::StartScene(QObject *parent)
    :QGraphicsScene(parent)
{
    logo = new Logo("res/logo.png");
    setSceneRect(QRectF(0, 0, 1280, 700));
    //addItem(logo);
    qDebug() << QString("%1,%2").arg(this->sceneRect().width()).arg(this->sceneRect().height());
    logo->setPos((this->sceneRect().width() - logo->boundingRect().width()) / 2, (this->sceneRect().height() - 2.7 * logo->boundingRect().height()) / 2);
    logo->setToolTip("Greed Play Blue Moon!");
    logo->setVisible(true);
    this->setBackgroundBrush(QPixmap("res/bg.jpg"));
}

StartScene::~StartScene()
{
    if (logo)
        logo->deleteLater();

}

Logo::Logo(const QString &filename)
{
    if (!QFile::exists(filename)) {

    }
    pixmap = QPixmap(filename);
}

QRectF Logo::boundingRect() const
{
    return pixmap.rect();
}

void Logo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(0, 0, pixmap);
}


