#pragma once

#include <QGraphicsObject>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>

class ItemIcon : public QGraphicsObject {
    Q_OBJECT
public:
    ItemIcon(const QString &name);
    ~ItemIcon();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private slots:
    void dealScale();
private:
    QString name;
};


class InfoBanner final : public QGraphicsObject {
    Q_OBJECT
public:

    const static int INFO_HEIGHT = 40;
    const static int ITEM_HEIGHT = 60;

    InfoBanner();
    ~InfoBanner();

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    void updateLayout();
public slots:
    void updateLevel(int level);
    void updateProperty();
    void updateHp();
    void updateGeneral();
private:
    void initializeText();
    void initializerItems();

    QGraphicsSimpleTextItem *general_name;
    QGraphicsSimpleTextItem *Hp;
    QGraphicsSimpleTextItem *level;
    QGraphicsTextItem *player_property;
    QList<ItemIcon *> items;

};
