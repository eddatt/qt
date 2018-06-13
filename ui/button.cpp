#include "button.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QFont>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QPropertyAnimation>



Button::Button(const QString &display_value, double w, double h)
    :value(display_value), text_item(nullptr), wx(w), hx(h)
{
    text_item = new QGraphicsTextItem(display_value,this);  // freed when parent is freed.
    text_item->setDefaultTextColor(QColor("white"));
    text_item->setFont(getButtonFont());
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
}

Button::~Button()
{
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

const QFont & Button::getButtonFont()
{
    static QFont f = QFont("Microsoft YaHei", 20);
    return f;
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
{
    setToolTip(general);
    if (!QFile::exists(QString("res/%1.png").arg(icon))) {
        QMessageBox::warning(nullptr, "Image No Found", QString("Cannot found the image %1 !").arg(QString("res/%1.png").arg(icon)));
    }
    this->icon = QPixmap(QString("res/%1.png").arg(icon));
    this->icon = this->icon.scaled(QSize(150, 150));
    setOpacity(0.5);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
}

AvatarButton::~AvatarButton()
{

}

QRectF AvatarButton::boundingRect() const
{
    return QRectF(0,0,150,150);
}

void AvatarButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    painter->drawPixmap(0,0,this->icon);
}

void AvatarButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void AvatarButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit this->click(this->toolTip());
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
