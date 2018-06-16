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

QRectF InfoBanner::boundingRect() const
{
    double width = UIUtility::getGraphicsSceneRect().width();
    return QRectF(0, 0, width, INFO_HEIGHT + ITEM_HEIGHT);
}

void InfoBanner::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setBrush(QColor("#7B7687"));
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, boundingRect().width(), INFO_HEIGHT);
}

InfoBanner::~InfoBanner()
{
    delete level;
    delete Hp;
    delete general_name;
}

InfoBanner::InfoBanner()
    :current_level(0)
{
    
    initializeText();
    initializerItems();

}

void InfoBanner::initializeText()
{
    this->general_name = new QGraphicsSimpleTextItem;
    general_name->setText(HumanPlayer::getInstance()->general());
    general_name->setBrush(QColor("white"));
    general_name->setFont(UIUtility::getInfoBarnerFont());
    general_name->setParentItem(this);
    general_name->setPos(50, INFO_HEIGHT/2 - general_name->boundingRect().height() / 2);

    double currentX = 50 + general_name->boundingRect().width() + 50;

    this->Hp = new QGraphicsSimpleTextItem;
    Hp->setText(QString("%1 / %1").arg(HumanPlayer::getInstance()->hp()).arg(HumanPlayer::getInstance()->maxHp()));
    Hp->setBrush(QColor("red"));
    Hp->setFont(UIUtility::getInfoBarnerFont());
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

    this->level = new QGraphicsSimpleTextItem;
    level->setText(QString("Level %1").arg(current_level));
    level->setBrush(QColor("white"));
    level->setFont(UIUtility::getInfoBarnerFont());
    level->setParentItem(this);
    level->setPos(currentX, INFO_HEIGHT/2 - level->boundingRect().height() / 2);

}

void InfoBanner::initializerItems()
{
    double currentX = 30;
    for (const auto &p : HumanPlayer::getInstance()->items()) {
        ItemIcon *i = new ItemIcon(p->name());
        i->setParentItem(this);
        i->setParent(this);
        i->setPos(currentX, INFO_HEIGHT + (ITEM_HEIGHT - 40)/2);
        currentX += 130;
    }
}

ItemIcon::ItemIcon(const QString &name)
{
    this->name = name;
    this->setAcceptHoverEvents(true);
    setOpacity(0.7);
}

ItemIcon::~ItemIcon()
{

}

QRectF ItemIcon::boundingRect() const
{
    return QRectF(0, 0, 40, 40);
}

void ItemIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(0,0, UIUtility::getPixmap("items", name, QSize(40, 40)));
    painter->setPen(QColor("white"));
    painter->drawPath(this->opaqueArea());
}

void ItemIcon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setOpacity(1.0);
}

void ItemIcon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QPropertyAnimation *ani = new QPropertyAnimation(this, "opacity");
    ani->setDuration(100);
    ani->setEndValue(0.7);
    ani->start(QAbstractAnimation::DeleteWhenStopped);
}

void ItemIcon::dealScale()
{
    this->prepareGeometryChange();
}

