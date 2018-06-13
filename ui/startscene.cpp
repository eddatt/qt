#include "startscene.h"
#include "ui/button.h"
#include <QFile>
#include <QPainter>
#include <QPixmap>
#include <QtDebug>
#include <QMessageBox>
#include <QGraphicsItemGroup>

StartScene::StartScene(QObject *parent)
    :QGraphicsScene(parent),choose_general(nullptr)
{
    logo = new Logo("res/logo.png");
    setSceneRect(QRectF(0, 0, 1280, 700));
    addItem(logo);
    qDebug() << QString("%1,%2").arg(this->sceneRect().width()).arg(this->sceneRect().height());
    logo->setPos((this->sceneRect().width() - logo->boundingRect().width()) / 2, (this->sceneRect().height() - 3.2 * logo->boundingRect().height()) / 2);
    logo->setToolTip("Greed Play Blue Moon!");
    logo->setVisible(true);
    this->setBackgroundBrush(QPixmap("res/bg.jpg"));
    createMenu();
}

StartScene::~StartScene()
{
    if (logo)
        logo->deleteLater();

}

void StartScene::createMenu()
{
    Button *start = new Button("Start Game");
    addItem(start);
    start->setPos((this->sceneRect().width() - start->boundingRect().width()) / 2, logo->y() + logo->boundingRect().height() + 80);

    buttons << start;

    auto w = start->boundingRect().width();
    auto h = start->boundingRect().height();
    auto x = start->x();
    auto y = start->y();

    y += 40 + h;

    Button *about = new Button("About", w, h);
    addItem(about);
    about->setPos(x, y);
    buttons << about;

    QObject::connect(about, &Button::click, [this] {
        QMessageBox::about(nullptr, "About", "GouliGuoJiaShengSiYi");
    });

    y += 40 + h;

    Button *exit_b = new Button("Exit", w, h);
    addItem(exit_b);
    exit_b->setPos(x, y);
    buttons << exit_b;

    QObject::connect(exit_b, &Button::click, []{
        exit(0);
    });

}

void StartScene::createCooseGeneralPannel()
{
    if (choose_general != nullptr)
        return;
    
    // title!

}

Logo::Logo(const QString &filename)
{
    if (!QFile::exists(filename)) {
        QMessageBox::warning(nullptr, "Image No Found", QString("Cannot found the image %1 !").arg(filename));
        return;
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

QRectF ChooseGeneralPanel::boundingRect() const
{
    return QRectF(0,0,0,0);

}

void ChooseGeneralPanel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{

}

void ChooseGeneralPanel::parse(const QStringList &generals)
{
    for (auto &s : generals) {
        this->buttons[s] = new AvatarButton(s, s);
    }


}
