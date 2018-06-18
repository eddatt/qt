#pragma once

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QGraphicsTextItem>
#include <QGraphicsDropShadowEffect>

class AI;
class AbstractPlayer;
class InfoBanner;
class DashBoard;
class CardItem;

class HpBar;
class PlayerAvatarContainer;
class MarkItem;

class PlayerInfoContainer final: public QGraphicsObject {
    Q_OBJECT
public:
    PlayerInfoContainer(AbstractPlayer *player = nullptr);
    ~PlayerInfoContainer();

    void createMarkItem();

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void setTargetSelect(bool is_select);

signals:
    void clicked(AbstractPlayer *);

public slots:
    void setHp(int hp,int max_hp);
    void setAlive(bool alive);
    void updateMark(const QString &mark);
    void setCurrent(bool current);
private:
    PlayerAvatarContainer * avatar;
    HpBar * bar;
    AbstractPlayer *player;
    QStringList marks_key;
    QList<MarkItem *> marks_value;
    QGraphicsDropShadowEffect *boundary;

};

class GameScene final : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject *parent);
    ~GameScene();

    inline int getCurrentLevel();

    DashBoard *dashBoard() const {
        return dash_board;
    }

signals:
    void endRount();

public slots:
    void selectReply(AbstractPlayer *player);
    void prepareGame();
    void run();

    void prepareFortargetSelect(bool is_select);

private:
    void createAIContainer();
    QList<PlayerInfoContainer *> ai_containers;
    InfoBanner* barner;
    DashBoard *dash_board;

    CardItem *current_judge_card;
};
                          