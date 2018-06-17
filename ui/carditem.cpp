#include "carditem.h"
#include "uiutility.h"
#include "logic/card.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsDropShadowEffect>

CardItem::CardItem(Card *c)
    :card(c), is_pop(false), in_animation(false), deleting(false)
{
    name = c->name();
    QObject::connect(this, &QGraphicsObject::enabledChanged, [this]() {
        setOpacity(this->isEnabled() ? 1 : 0.3);
    });
    boundary = new QGraphicsDropShadowEffect(this);
    boundary->setOffset(0);
    boundary->setBlurRadius(18);
    boundary->setColor("white");
    boundary->setEnabled(false);
    setGraphicsEffect(boundary);
    setZValue(3);
    setAcceptHoverEvents(true);
}

QRectF CardItem::boundingRect() const
{
    return QRectF(0, 0, 97, 134);
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(2,2, UIUtility::getPixmap("cards", name));
}

CardItem::~CardItem()
{
    delete boundary;
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!in_animation && !deleting)
        emit clicked();
}

void CardItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setZValue(10);
    if (is_pop) return;
    boundary->setEnabled(true);
}

void CardItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setZValue(3);
    if (is_pop) return;
    boundary->setEnabled(false);
}

QTimeLine * CardItem::animateMoveTo(qreal x, qreal y, int duration, QTimeLine *out)
{
    QGraphicsItemAnimation *anima = new QGraphicsItemAnimation(this);
    QTimeLine *tl;
    if (out == nullptr)
        tl = new QTimeLine(duration, this);
    else
        tl = out;
    QObject::connect(tl, &QTimeLine::finished, tl, &QTimeLine::deleteLater);
    tl->setFrameRange(0, 200);
    anima->setTimeLine(tl);
    anima->setItem(this);
    qreal deltax = x - this->x();
    qreal deltay = y - this->y();
    for (int i = 0; i <= tl->endFrame(); ++i) {
        anima->setPosAt(double(i)/tl->endFrame(),QPointF(this->x() + deltax * i / 200, this->y() + deltay * i / 200));
    }
    QObject::connect(tl, &QTimeLine::finished, anima, &QGraphicsItemAnimation::deleteLater);
    if (x > UIUtility::getGraphicsSceneRect().width() || y > UIUtility::getGraphicsSceneRect().height()) {
        QObject::connect(tl, &QTimeLine::finished, [this]() {
            emit this->outofScene(deleting);
        });
    }
    QObject::connect(tl, &QTimeLine::stateChanged, this, &CardItem::dealAnimationStatedChanged);
    return tl;
}

void CardItem::pop()
{
    if (deleting) return;
    if (is_pop) return;
    animateMoveTo(this->x(), this->y() - 30, 200)->start();
    boundary->setColor("gold");
    boundary->setEnabled(true);
    is_pop = true;
}

void CardItem::resetPop()
{
    if (deleting) return;
    if (!is_pop) return;
    is_pop = false;
    animateMoveTo(this->x(), this->y() + 30, 200)->start();
    boundary->setColor("white");
    boundary->setEnabled(false);
}

void CardItem::dealAnimationStatedChanged(QTimeLine::State newState)
{
    if (newState == QTimeLine::Running)
        in_animation = true;
    else
        in_animation = false;
}

void CardItem::decoupled()
{
    deleting = true;
    setEnabled(false);
    hide();
    setParentItem(nullptr);
    delete this;
}

