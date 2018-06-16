#include "dash_board.h"
#include "uiutility.h"
#include "logic/player.h"
#include "PlayerAvatarContainer.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>


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
    painter->drawRect(boundingRect());
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
        127 - magic_item->boundingRect().height() / 2);
    bar = new HpBar(this->sceneBoundingRect().width(),HumanPlayer::getInstance()->maxHp(),HumanPlayer::getInstance()->hp());
    bar->setParent(this);
    bar->setParentItem(this);
    bar->setPos(0, this->boundingRect().height() - bar->boundingRect().height() - 5);

    container = new PlayerAvatarContainer(HumanPlayer::getInstance());
    container->setParent(this);
    container->setParentItem(this);
    container->setPos(0, 0);
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

