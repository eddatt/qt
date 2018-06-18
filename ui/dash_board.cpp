#include "dash_board.h"
#include "uiutility.h"
#include "logic/player.h"
#include "PlayerAvatarContainer.h"
#include "carditem.h"
#include "logic/card.h"
#include "gamescene.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>


/*
__________________                                 
Effect and Marks                                  
________________________________________________________________________________
DashBoard|                                         |           |            |   |
         |                                         |           |            | H |
         |                                         |           |            |   |
         |               Cards                     |           |   Avatar   |   |
         |                                         |           |            |   |
         |                                         |           |            | P |
_________|_________________________________________|___________|____________|___|
*/


QRectF DashBoard::boundingRect() const
{
    double width = UIUtility::getGraphicsSceneRect().width();
    return QRectF(0, 0, width, 255);
}

void DashBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    //painter->drawRect(boundingRect());
}

DashBoard::~DashBoard()
{

}

DashBoard::DashBoard()
{
    createMarkRegion();
    magic_item = new MagicIndexItem;
    magic_item->setParent(this);
    magic_item->setParentItem(this);
    magic_item->setPos(UIUtility::getGraphicsSceneRect().width() - (250 - magic_item->boundingRect().width() / 2), 
        127 - magic_item->boundingRect().height() / 2 - 10);

    QObject::connect(magic_item, &MagicIndexItem::clicked, HumanPlayer::getInstance(), &HumanPlayer::endRound);
    QObject::connect(HumanPlayer::getInstance(), &HumanPlayer::magicChanged, magic_item,&MagicIndexItem::updateMagic);
    QObject::connect(HumanPlayer::getInstance(), &HumanPlayer::maxMagicChanged, magic_item, &MagicIndexItem::updateMagic);
    bar = new HpBar(this->sceneBoundingRect().width(),HumanPlayer::getInstance()->maxHp(),HumanPlayer::getInstance()->hp());
    bar->setParent(this);
    bar->setParentItem(this);
    bar->setPos(0, this->boundingRect().height() - bar->boundingRect().height() - 5);

    QObject::connect(HumanPlayer::getInstance(), &AbstractPlayer::hpChanged, [this]() {
        this->bar->setCurrentHp(HumanPlayer::getInstance()->hp());
    });
    QObject::connect(HumanPlayer::getInstance(), &AbstractPlayer::maxHpChanged, [this]() {
        this->bar->setHp(HumanPlayer::getInstance()->hp(), HumanPlayer::getInstance()->maxHp());
    });

    container = new PlayerAvatarContainer(HumanPlayer::getInstance());
    container->setParent(this);
    container->setParentItem(this);
    container->setPos(0, 0);

    QObject::connect(HumanPlayer::getInstance(), &AbstractPlayer::aliveChanged, container, &PlayerAvatarContainer::updateAlive);

    card_manager = new CardItemManager;
    card_manager->setParent(this);
    card_manager->setParentItem(this);
    card_manager->setPos(container->boundingRect().width() + 5, 0);
}

void DashBoard::createMarkRegion()
{
    for (auto &p : marks_value) {
        if(p)
            p->deleteLater();
    }    
    marks_key.clear();
    marks_value.clear();
    int currentX = UIUtility::getGraphicsSceneRect().width()-60;
    for (auto &s : HumanPlayer::getInstance()->getMarks()) {
        if (HumanPlayer::getInstance()->markNumber(s) > 0) {
            marks_key.push_back(s);
            MarkItem *mark_item = new MarkItem(s, HumanPlayer::getInstance()->markNumber(s));
            mark_item->setParent(this);
            mark_item->setParentItem(this);
            mark_item->setPos(currentX, 0);
            marks_value.push_back(mark_item);
            currentX -= 40;
        }
    }

}

void DashBoard::updateMark(const QString &name)
{
    if (marks_key.contains(name)) {
        // update number;
        if (HumanPlayer::getInstance()->markNumber(name) > 0) {
            marks_value.at(marks_key.indexOf(name))->setNumber(HumanPlayer::getInstance()->markNumber(name));
        }
        else {
            // create new
            createMarkRegion();
        }
    }
    else {
        marks_key << name;
        MarkItem *item = new MarkItem(name, HumanPlayer::getInstance()->markNumber(name));
        item->setParent(this);
        this->setParentItem(this);
        this->setPos(UIUtility::getGraphicsSceneRect().width() - marks_key.length() * 40 + 60, 0);
        marks_value << item;
    }
}

void DashBoard::addCardItem(CardItem *add)
{
    this->card_manager-> addCardItem(add);
}

void DashBoard::removeCardItem(CardItem *re)
{
    this->card_manager->removeCardItem(re);
}

void DashBoard::addCardItems(const QList<CardItem*>& items)
{
    this->card_manager->addCardItems(items);
}

void DashBoard::removeAllCardItem()
{
    this->card_manager->removeAllCardItem();
}

void DashBoard::setCurrent(bool current)
{
    qobject_cast<GameScene *>(scene())->prepareFortargetSelect(false);
    if (current != true)
        card_manager->unselectCard();
    magic_item->setEnabled(current);
    card_manager->setEnabled(current);
}

QRectF MarkItem::boundingRect() const
{
    return QRectF(0, 0, 35, 35);
}

MarkItem::MarkItem(const QString &name, int number /*= 1*/)
{
    this->m_name = name;
    this->m_number = number;
    this->number_item = new QGraphicsSimpleTextItem(QString::number(number),this);
    number_item->setFont(UIUtility::getMarkNumberFont());
    number_item->setBrush(QColor("white"));
    number_item->setParentItem(this);
    number_item->setPos(this->boundingRect().width() - number_item->boundingRect().width(), this->boundingRect().height() - number_item->boundingRect().height());
}

void MarkItem::setNumber(int n)
{
    this->m_number = n;
    prepareGeometryChange();
    this->number_item->setText(QString::number(n));
    update();
}

void MarkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(0, 0, UIUtility::getPixmap("marks", m_name, QSize(30, 30)));
    number_item->setZValue(10);
}

MarkItem::~MarkItem()
{
    delete number_item;
}

MagicIndexItem::MagicIndexItem()
    :hovered(false)
{
    magic = new QGraphicsSimpleTextItem(QString("%1 / %2").arg(HumanPlayer::getInstance()->magic())
        .arg(HumanPlayer::getInstance()->maxMagic()));
    magic->setFont(UIUtility::getDefaultFont());
    magic->setBrush(QColor("#c7d8ff"));
    magic->setPos((boundingRect().width() - magic->boundingRect().width()) / 2, (boundingRect().height() - magic->boundingRect().height()) / 2);
    magic->setParentItem(this);
    setAcceptHoverEvents(true);
}

QRectF MagicIndexItem::boundingRect() const
{
    return QRectF(0, 0, qMax<double>(100,magic->boundingRect().width()), qMax<double>(100, magic->boundingRect().width()));
}

void MagicIndexItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    magic->setZValue(10);
    //painter->drawPixmap(0, 0, UIUtility::getPixmap("system", "magic", QSize(boundingRect().height(), boundingRect().width())));
    static QPen tmp;
    tmp.setColor("#184aad");
    tmp.setWidth(5);
    painter->setPen(tmp);
    painter->drawRoundedRect(boundingRect(), 10, 10);

    
}

MagicIndexItem::~MagicIndexItem()
{
    delete magic;
}

void MagicIndexItem::updateMagic()
{
    if (!hovered) {
        magic->setText(QString("%1 / %2").arg(HumanPlayer::getInstance()->magic()).arg(HumanPlayer::getInstance()->maxMagic()));
        magic->setPos((boundingRect().width() - magic->boundingRect().width()) / 2, (boundingRect().height() - magic->boundingRect().height()) / 2);
    }
        
}

void MagicIndexItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    hovered = true;
    magic->setText("End");
    magic->setPos((boundingRect().width() - magic->boundingRect().width()) / 2, (boundingRect().height() - magic->boundingRect().height()) / 2);
}

void MagicIndexItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    hovered = false;
    updateMagic();

}

void MagicIndexItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void MagicIndexItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    hovered = false;
    updateMagic();
    emit clicked();
}

void CardItemManager::updateCardItemLayout()
{
    // QRectF(0, 0, 177, 233)
    double from_x = boundingRect().center().x() -(card_items.length() / 2.0) * 93;
    QTimeLine *tl = new QTimeLine(1000,this);
    QObject::connect(tl, &QTimeLine::finished, tl, &QTimeLine::deleteLater);
    for (auto &c : card_items) {
        c->animateMoveTo(from_x, c->y(), 500, tl);
        c->setAvailable(c->cardInfo()->isAvailable());
        from_x += 93;
    }
    tl->start();
}

CardItemManager::CardItemManager()
    :current_activate(nullptr)
{
    QList<CardItem *> tmp;
    for (auto &c : HumanPlayer::getInstance()->cards()) {
        tmp << c->cardItem();
    }
    addCardItems(tmp);
}

CardItemManager::~CardItemManager()
{
}

QRectF CardItemManager::boundingRect() const
{
    return QRectF(0, 0, UIUtility::getGraphicsSceneRect().width() -  440, 238);
}

void CardItemManager::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{

}

QList<CardItem *> CardItemManager::cardItems()
{
    return card_items;
}

void CardItemManager::addCardItems(const QList<CardItem *> &items)
{
    for (auto &c : items) {
        c->setParentItem(this);
        //c->setPos(0, 0);
        c->setPos(-100, boundingRect().center().y() - c->boundingRect().center().y());
        QObject::connect(c, &CardItem::clicked, this, &CardItemManager::onSelectCard);
        card_items << c;
    }
    updateCardItemLayout();
}

void CardItemManager::addCardItem(CardItem *add)
{
    if (card_items.contains(add)) return;
    add->setParentItem(this);
    add->setPos(-1 - x() - add->boundingRect().x(), boundingRect().center().y() - add->boundingRect().center().y());
    card_items << add;
    QObject::connect(add, &CardItem::clicked, this, &CardItemManager::onSelectCard);
    updateCardItemLayout();
}

void CardItemManager::removeAllCardItem()
{
    unselectCard();
    QTimeLine *tl = new QTimeLine(500);
    QObject::connect(tl, &QTimeLine::finished, tl, &QTimeLine::deleteLater);
    for (auto &c : card_items) {
        c->animateMoveTo(this->scene()->width() + 100, c->y(), 200, tl);
        QObject::disconnect(c, &CardItem::clicked, this, &CardItemManager::onSelectCard);
        QObject::connect(tl, &QTimeLine::finished, c, &CardItem::decoupled);
    }
    tl->start();
    card_items.clear();
}

void CardItemManager::removeCardItem(CardItem *re)
{
    if (card_items.contains(re)) {
        if (current_activate == re)
            unselectCard();
        card_items.removeAll(re);
        auto tl = re->animateMoveTo(this->scene()->width() + 100, re->y(), 500);
        QObject::disconnect(re, &CardItem::clicked, this, &CardItemManager::onSelectCard);
        QObject::connect(tl, &QTimeLine::finished, re, &CardItem::decoupled);
        tl->start();
    }
    updateCardItemLayout();
}

void CardItemManager::useCardAnimation()
{
        
}

void CardItemManager::selectCard(CardItem *item)
{
    if (item == currentSelected()) {
        unselectCard();
        emit selectChanged(false);
        return;
    }
    unselectCard();
    this->current_activate = item;
    item->pop();
    emit selectChanged(true);
    for (auto &c : card_items) {
        if (c == item) continue;
        c->setOpacity(0.8);
    }
}

void CardItemManager::onSelectCard()
{
    selectCard(qobject_cast<CardItem *>(sender()));
}

CardItem * CardItemManager::currentSelected() const
{
    return current_activate;
}

void CardItemManager::unselectCard()
{
    if (current_activate) {
        current_activate->resetPop();
        emit selectChanged(false);
    }
    current_activate = nullptr;
    //updateCardItemLayout();
}
