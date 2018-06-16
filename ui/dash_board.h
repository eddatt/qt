#pragma once
#include <QGraphicsObject>
#include <QGraphicsSimpleTextItem>

class HpBar;
class PlayerAvatarContainer;
class MarkItem final : public QGraphicsObject {
    Q_OBJECT
public:
    MarkItem(const QString &name,int number = 1);
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    inline int number() const {
        return this->m_number;
    }
    inline QString name() const {
        return m_name;
    }
    void setNumber(int n);
    ~MarkItem();
private:
    QString m_name;
    int m_number;
    QGraphicsSimpleTextItem *number_item;
};

class MagicIndexItem final : public QGraphicsObject {
    Q_OBJECT
public:
    MagicIndexItem();
    ~MagicIndexItem();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void clicked();
public slots:
    void updateMagic();
private:
    QGraphicsSimpleTextItem *magic;

    bool hovered;
};


class DashBoard final : public QGraphicsObject {
    Q_OBJECT
public:
    DashBoard();
    ~DashBoard();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    void createMarkRegion();

public slots:
    void updateMark(const QString &name);
private:
    QStringList marks_key;
    QList<MarkItem *> marks_value;
    HpBar *bar;
    MagicIndexItem *magic_item;
    PlayerAvatarContainer *container;
};