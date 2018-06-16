#pragma once

#include <QGraphicsObject>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsRectItem>

class AbstractPlayer;

class HpBar : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(int current_hp READ currentHp WRITE setCurrentHp)
public:
    HpBar(double w_width, int max = 80, int current = 80);
    ~HpBar();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;
    inline int currentHp() const {
        return current_hp;
    }
    void setCurrentHp(int hp) {
        setHp(hp, max_hp);
    }
    QColor getBrushColor() const;
    static const QFont &textFont();
public slots:
    void setHp(int hp,int max_hp);
private:
    QGraphicsTextItem * hp;
    double w;
    int max_hp;
    int current_hp;
};

class PlayerAvatarContainer : public QGraphicsObject
{
    Q_OBJECT
public:
    PlayerAvatarContainer(AbstractPlayer *owner);
    ~PlayerAvatarContainer();
    
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    static void convertToGray(QPixmap &pix);

public slots:
    void updateAlive(bool alive);
private:
    AbstractPlayer *m_owner;
    bool alive;
};
