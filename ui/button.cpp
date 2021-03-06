#include "button.h"
#include "ui/uiutility.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QFont>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>




Button::Button(const QString &display_value, double w, double h)
    :value(display_value), text_item(nullptr), wx(w), hx(h)
{
    text_item = new QGraphicsTextItem(display_value,this);  // freed when parent is freed.
    text_item->setDefaultTextColor(QColor("white"));
    text_item->setFont(UIUtility::getDefaultFont());
    text_item->setParentItem(this);
    double tx = 40, ty = 20;
    if (wx > 0) {
        tx = (wx - text_item->boundingRect().width()) / 2.0;
    }
    else {
        wx = text_item->boundingRect().width() + 80;
    }
        
    if(hx > 0)
        ty = (hx - text_item->boundingRect().height()) / 2.0;
    else {
        hx = text_item->boundingRect().height() + 40;
    }
    
    text_item->setPos(tx, ty);
    text_item->setZValue(10);
    text_item->setVisible(true);

    background_rect = new QGraphicsRectItem(this);
    static QPen tmp;
    tmp.setWidth(5);
    tmp.setBrush(QColor("white"));
    tmp.setJoinStyle(Qt::RoundJoin);

    background_rect->setPen(tmp);
    background_rect->setBrush(QColor("black"));
    background_rect->setRect(boundingRect());
    background_rect->setParentItem(this);
    background_rect->setZValue(1);
    background_rect->setVisible(true);

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    connect(this, &Button::enabledChanged, [this]() {
        if (this->isEnabled())
            this->setOpacity(1);
        else
            this->setOpacity(0.43);
    });
}

Button::~Button()
{
    if (text_item)
        text_item->deleteLater();
    if (background_rect)
        delete background_rect;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    text_item->setDefaultTextColor("white");
    background_rect->setBrush(QColor("black"));
    emit this->click();
}

QRectF Button::boundingRect() const
{
    return QRectF(0, 0, this->wx, this->hx);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{

}


void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    text_item->setDefaultTextColor("white");
    background_rect->setBrush(QColor("black"));
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    text_item->setDefaultTextColor("black");
    background_rect->setBrush(QColor("white"));
}

AvatarButton::AvatarButton(const QString &general, const QString &icon)
    :QGraphicsObject(nullptr),value(general), boundary(nullptr), m_icon(icon)
{
    setToolTip(general);
    setOpacity(0.5);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    this->selected = false;
    this->boundary = new QGraphicsRectItem(this->boundingRect(),this);
    boundary->setParentItem(this);
    static QPen tmp;
    tmp.setWidth(5);
    tmp.setBrush(QColor("white"));
    tmp.setJoinStyle(Qt::RoundJoin);

    boundary->setPen(tmp);
    boundary->setBrush(Qt::NoBrush);

    boundary->show();
}

AvatarButton::~AvatarButton()
{
    if (boundary)
        delete boundary;

}

QRectF AvatarButton::boundingRect() const
{
    return QRectF(0,0,150,150);
}

void AvatarButton::setSelected(bool is_selected)
{
    this->selected = is_selected;
    setAcceptHoverEvents(!is_selected);
    static QPen tmp;
    tmp.setWidth(5);
    tmp.setJoinStyle(Qt::RoundJoin);
    if (selected) {
        tmp.setBrush(QColor("gold"));
        setOpacity(1);
    } else {
       setOpacity(0.5);
       tmp.setBrush(QColor("white"));
    }
    boundary->setPen(tmp);
        
}

void AvatarButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(0,0, UIUtility::getPixmap("general", m_icon, QSize(150, 150)));
}

void AvatarButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void AvatarButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit this->click(value);
}

void AvatarButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QPropertyAnimation *anima = new QPropertyAnimation(this, "opacity");
    anima->setEndValue(1);
    anima->setDuration(100);
    anima->start(QAbstractAnimation::DeleteWhenStopped);
}

void AvatarButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QPropertyAnimation *anima = new QPropertyAnimation(this, "opacity");
    anima->setEndValue(0.5);
    anima->setDuration(100);
    anima->start(QAbstractAnimation::DeleteWhenStopped);
}
