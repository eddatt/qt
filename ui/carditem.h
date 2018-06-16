#pragma once

#include <QGraphicsObject>
#include <QGraphicsRectItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class CardItem : public QGraphicsObject
{
    Q_OBJECT

public:
    CardItem(const QString &cardname);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    ~CardItem();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void animateMoveTo(qreal x, qreal y, int duration);
    void pop();
    void reset_pop();
signals:
    void clicked();
    void outofScene();
private:
    bool is_pop;
    bool in_animation;
    QString card_name;
    QGraphicsRectItem *boundary;
   
};
