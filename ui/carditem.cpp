#include "carditem.h"
#include "uiutility.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

CardItem::CardItem(const QString &cardname)
    :card_name(cardname), is_pop(false), in_animation(false)
{
    QObject::connect(this, &QGraphicsObject::enabledChanged, [this]() {
        setOpacity(this->isEnabled() ? 1 : 0.3);
    });
    boundary = new QGraphicsRectItem(boundary);
    static QPen tmp;
    tmp.setWidth(5);
    tmp.setColor("white");
    boundary->setPen(tmp);
    boundary->setOpacity(0.5);
    boundary->setParentItem(this);
    boundary->hide();
}

QRectF CardItem::boundingRect() const
{
    return QRectF(0, 0, 177, 233);
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(0,0, UIUtility::getPixmap("cards", card_name, QSize(boundingRect().width(), boundingRect().height())));
    boundary->hide();
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
    if(!in_animation)
        emit clicked();
}

void CardItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    boundary->show();
}

void CardItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    boundary->hide();
}

void CardItem::animateMoveTo(qreal x, qreal y, int duration)
{
    QGraphicsItemAnimation *anima = new QGraphicsItemAnimation(this);
    QTimeLine *tl = new QTimeLine(duration,this);
    tl->setFrameRange(0, 200);
    anima->setTimeLine(tl);
    anima->setItem(this);
    qreal deltax = x - this->x();
    qreal deltay = y - this->y();
    for (int i = 0; i <= 200; ++i) {
        anima->setPosAt(i,QPointF(this->x() + deltax * i / 200, this->y() + deltay * i / 200));
    }
    QObject::connect(tl, &QTimeLine::finished, tl, &QTimeLine::deleteLater);
    QObject::connect(tl, &QTimeLine::finished, anima, &QTimeLine::deleteLater);
    if (x > this->scene()->width() || y > this->scene()->height()) {
        QObject::connect(tl, &QTimeLine::finished, this, &CardItem::outofScene);
    }
    QObject::connect(tl, &QTimeLine::finished, [this]() {
        this->in_animation = false;
    });
    in_animation = true;
    tl->start();
}

void CardItem::pop()
{
    is_pop = true;
    animateMoveTo(this->x(), this->y() + 50, 100);
}

void CardItem::reset_pop()
{
    is_pop = true;
    animateMoveTo(this->x(), this->y() - 50, 100);
}
