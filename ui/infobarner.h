#pragma once

#include <QGraphicsObject>
#include <QGraphicsTextItem>

class ItemIcon : public QGraphicsObject {
    Q_OBJECT
public:
    ItemIcon(const QString &name);
    ~ItemIcon();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
private:
    QString name;
    QPixmap px;
};


class InfoBanner final : public QGraphicsObject {
    Q_OBJECT
public:

    const static int INFO_HEIGHT = 50;
    const static int ITEM_HEIGHT = 100;

    static InfoBanner *getInstance();
    ~InfoBanner();

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;
private:
    InfoBanner();

    void initializeText();
    void initializerItems();

    QGraphicsTextItem *general_name;
    QGraphicsTextItem *Hp;
    QGraphicsTextItem *level;
    QGraphicsTextItem *player_property;
    QList<ItemIcon *> items;

    int current_level;
};
