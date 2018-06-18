#include "PlayerAvatarContainer.h"
#include "uiutility.h"
#include "logic/player.h"

#include <QFont>
#include <QPainter>

PlayerAvatarContainer::PlayerAvatarContainer(AbstractPlayer *owner)
    :m_owner(owner),alive(true)
{
    
}

PlayerAvatarContainer::~PlayerAvatarContainer()
{
}


QRectF PlayerAvatarContainer::boundingRect() const
{
    return QRectF(0, 0, 177, 240);
}

void PlayerAvatarContainer::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    if (!alive)
        painter->drawPixmap(0,0, UIUtility::getPixmap("avatar", m_owner->general(), QSize(boundingRect().width(),boundingRect().height()), true));
    else 
        painter->drawPixmap(0, 0, UIUtility::getPixmap("avatar", m_owner->general(), QSize(boundingRect().width(), boundingRect().height())));
    painter->drawPixmap(0, 0, UIUtility::getPixmap("system", "frame", QSize(boundingRect().width(), boundingRect().height())));
}


void PlayerAvatarContainer::updateAlive(bool alive)
{
    this->alive = alive;
    update();
}

HpBar::HpBar(double w_width, int max, int current /*= 0*/)
    : max_hp(max), current_hp(current), w(w_width)
{
    hp = new QGraphicsTextItem(QString("%1 / %2").arg(current).arg(max));
    hp->setParent(this);
    hp->setParentItem(this);
    hp->setFont(textFont());
    hp->setDefaultTextColor("white");
    hp->setPos(w / 2 - hp->boundingRect().width() / 2, this->boundingRect().height() / 2 - hp->boundingRect().height() / 2);
}

HpBar::~HpBar()
{

}


QRectF HpBar::boundingRect() const
{
    return QRectF(0, 0, w, 10);
}

void HpBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(getBrushColor());
    painter->drawRoundedRect(0, 0, w *current_hp / qreal(max_hp), 10, 3, 3);
}

QColor HpBar::getBrushColor() const
{
    double rate = current_hp / qreal(max_hp);
    if (rate > 0.7) {
        return QColor("green");
    }
    else if (rate > 0.4) {
        return QColor("yellow");
    }
    else {
        return QColor("red");
    }
}

const QFont & HpBar::textFont()
{
    static QFont f = QFont("Microsoft YaHei", 5);
    return f;
}

void HpBar::setHp(int hp, int max_hp)
{
    this->current_hp = hp;
    this->max_hp = max_hp;
    this->hp->setPlainText(QString("%1 / %2").arg(current_hp).arg(max_hp));
    this->hp->setPos(w / 2 - this->hp->boundingRect().width() / 2, this->boundingRect().height() / 2 - this->hp->boundingRect().height() / 2);
    update(boundingRect());
}
