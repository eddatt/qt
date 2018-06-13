#include "startscene.h"
#include "ui/button.h"
#include "logic/gamelogic.h"

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
    if (buttons.size() == 3) {
        if (choose_general && choose_general->isVisible())
            choose_general->hide();
        for (auto &p : buttons)
            p->show();
        return;
    }
    Button *start = new Button("Start Game");
    addItem(start);
    start->setPos((this->sceneRect().width() - start->boundingRect().width()) / 2, logo->y() + logo->boundingRect().height() + 80);

    buttons << start;

    auto w = start->boundingRect().width();
    auto h = start->boundingRect().height();
    auto x = start->x();
    auto y = start->y();
    QObject::connect(start, &Button::click, [this] {
        this->createCooseGeneralPannel();
    });

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
    for (auto &p : buttons) {
        if(p->isVisible())
            p->hide();
    }
    if (choose_general != nullptr) {
        choose_general->show();
        return;
    }
        
    
    choose_general = new ChooseGeneralPanel;
    
    this->addItem(choose_general);
    choose_general->setPos((this->sceneRect().width() - choose_general->boundingRect().width()) / 2, logo->y() + logo->boundingRect().height() + 80);
    choose_general->show();
    QObject::connect(choose_general, &ChooseGeneralPanel::onBackClicked, [this]() {
        this->createMenu();
    });
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
    double width = qMax<double>(buttons.size() * 150 + qMax<int>(buttons.size()-1,0)*40,title->boundingRect().width());
    double height = 190 + title->boundingRect().height() + (back != nullptr ? back->boundingRect().height() : 0) + 40;
    return QRectF(0, 0, width, height);
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

ChooseGeneralPanel::ChooseGeneralPanel(QGraphicsItem *parent /*= nullptr*/)
    :QGraphicsObject(parent), title(nullptr), back(nullptr)
{
    title = new QGraphicsTextItem("Please Choose A General To Go:");
    title->setFont(Button::getButtonFont());
    title->setDefaultTextColor("white");
    back = new Button("Back");
    parse(GameLogic::getInstance()->getAllGenerals());
    back->setParentItem(this);
    double mx = this->boundingRect().width() / 2;
    back->setPos(mx - back->boundingRect().width() / 2, 230 + title->boundingRect().height());
    back->show();
    QObject::connect(back, &Button::click, this, &ChooseGeneralPanel::onBackClicked);
    title->setParentItem(this);
    title->setPos(mx - title->boundingRect().width() / 2, 0);
    title->show();
    int i = 0;
    for (auto &b : buttons.values()) {
        b->setParentItem(this);
        b->setPos(i * 190, title->boundingRect().height() + 40);
        b->show();
        QObject::connect(b, &AvatarButton::click, this, &ChooseGeneralPanel::onGeneralChosen);
        ++i;
    }
}

ChooseGeneralPanel::~ChooseGeneralPanel()
{

}
