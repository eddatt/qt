#include <infobarner.h>
#include <QPainter>
#include <QPropertyAnimation>

#include "logic/item.h"
#include "gamescene.h"
#include "uiutility.h"
#include "logic/player.h"



/*
__________________________________________________________________________
General Name   Hp             Property          Position                 Cards
__________________________________________________________________________
Items
__________________________________________________________________________
*/
InfoBanner * InfoBanner::getInstance()
{
    static InfoBanner barner;
    return &barner;
}

QRectF InfoBanner::boundingRect() const
{
    double width = GameScene::getInstance()->width();
    return QRectF(0, 0, width, INFO_HEIGHT + ITEM_HEIGHT);
}

void InfoBanner::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setBrush(QColor("#495A80"));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, boundingRect().width(), INFO_HEIGHT);
}

InfoBanner::~InfoBanner()
{

}

InfoBanner::InfoBanner()
    :current_level(0)
{
    initializeText();
    initializerItems();

}

void InfoBanner::initializeText()
{
    this->general_name = new QGraphicsTextItem;
    general_name->setPlainText(HumanPlayer::getInstance()->general());
    general_name->setDefaultTextColor("white");
    general_name->setFont(UIUtility::getInfoBarnerFont());
    general_name->setParent(this);
    general_name->setParentItem(this);
    general_name->setPos(50, INFO_HEIGHT/2 - general_name->boundingRect().height() / 2);

    double currentX = 50 + general_name->boundingRect().width() + 50;

    this->Hp = new QGraphicsTextItem;
    Hp->setPlainText(QString("%1 / %1").arg(HumanPlayer::getInstance()->hp()).arg(HumanPlayer::getInstance()->maxHp()));
    Hp->setDefaultTextColor("red");
    Hp->setFont(UIUtility::getInfoBarnerFont());
    Hp->setParent(this);
    Hp->setParentItem(this);
    Hp->setPos(currentX, INFO_HEIGHT/2 - Hp->boundingRect().height() / 2);
    currentX += Hp->boundingRect().width() + 100;

    this->player_property = new QGraphicsTextItem;
    player_property->setHtml(QString("<font color = \"red\">%1</font> / <font color = \"green\">%2</font> / <font color = \"blue\">%3</font>").arg(
        QString::number(HumanPlayer::getInstance()->power()), QString::number(HumanPlayer::getInstance()->agility()), QString::number(HumanPlayer::getInstance()->intelligence())
    ));
    player_property->setFont(UIUtility::getInfoBarnerFont());
    player_property->setParent(this);
    player_property->setParentItem(this);
    player_property->setPos(currentX, INFO_HEIGHT/2 - player_property->boundingRect().height() / 2);

    currentX += player_property->boundingRect().width() + 100;

    this->level = new QGraphicsTextItem;
    level->setPlainText(QString("Level %1").arg(current_level));
    level->setDefaultTextColor("white");
    level->setFont(UIUtility::getInfoBarnerFont());
    level->setParent(this);
    level->setParentItem(this);
    level->setPos(currentX, INFO_HEIGHT/2 - level->boundingRect().height() / 2);

}

void InfoBanner::initializerItems()
{
    double currentX = 50;
    for (const auto &p : HumanPlayer::getInstance()->items()) {
        ItemIcon *i = new ItemIcon(p->name());
        i->setParentItem(this);
        i->setParent(this);
        i->setPos(currentX, 115);
        currentX += 130;
    }
}

ItemIcon::ItemIcon(const QString &name)
{
    this->name = name;
    this->px = UIUtility::getPixmap("items", name, QSize(70, 70));
    this->setAcceptHoverEvents(true);
}

ItemIcon::~ItemIcon()
{

}

QRectF ItemIcon::boundingRect() const
{
    return QRectF(0, 0, 70, 70);
}

void ItemIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(0,0,this->px);
}

void ItemIcon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setScale(8 / 7);
}

void ItemIcon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QPropertyAnimation *ani = new QPropertyAnimation(this, "scale");
    ani->setDuration(100);
    ani->setEndValue(1);
    ani->start(QAbstractAnimation::DeleteWhenStopped);
}

