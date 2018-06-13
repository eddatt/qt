#pragma once

#include <QGraphicsObject>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

class QFont;

class Button : public QGraphicsObject
{
    Q_OBJECT

public:
    Button(const QString &display_value = QString(), double w = -1, double h = -1);
    ~Button();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    static const QFont &getButtonFont();

signals:
    void click();
private:
    QString value;
    QGraphicsTextItem *text_item;
    QGraphicsRectItem *background_rect;
    double wx;
    double hx;
};

class AvatarButton : public QGraphicsObject {
    Q_OBJECT
public:
    AvatarButton(const QString &general, const QString &icon);
    ~AvatarButton();

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

signals:
    void click(QString general);
private:
    QPixmap icon;
    QString value;
    QGraphicsTextItem *text_item;
};
