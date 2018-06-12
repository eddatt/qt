#pragma once

#include <QGraphicsScene>
#include <QGraphicsObject>


class AvatarButton : public QGraphicsObject {
    Q_OBJECT
public:
    AvatarButton(const QString &general, const QString &icon);

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
signals:
    void click();
private:
    QString general;
    QPixmap icon;
};

class Logo : public QGraphicsObject {
     Q_OBJECT
public:
    Logo(const QString &filename);

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

private:
    QPixmap pixmap;

};

class StartScene : public QGraphicsScene
{
    Q_OBJECT

public:
    StartScene(QObject *parent);
    ~StartScene();
private:
    Logo * logo;
};
