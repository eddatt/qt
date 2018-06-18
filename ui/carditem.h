#pragma once

#include <QGraphicsObject>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class Card;
enum QTimeLine::State;

class QGraphicsDropShadowEffect;

class CardItem : public QGraphicsObject
{
    Q_OBJECT

public:
    CardItem(Card *card);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    ~CardItem();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    inline bool isAvailable() const {
        return available;
    }

    void setAvailable(bool ava);

    Card *cardInfo() const {
        return card;
    }

    QTimeLine *animateMoveTo(qreal x, qreal y, int duration, QTimeLine *out = nullptr);
    void pop();
    void resetPop();

public slots:
    void dealAnimationStatedChanged(QTimeLine::State newState);
    void decoupled();
signals:
    void clicked();
    void outofScene(bool);
private:
    bool deleting;
    bool is_pop;
    bool in_animation;
    bool available;
    QGraphicsDropShadowEffect *boundary;
    QString name;
    Card *card;
};
