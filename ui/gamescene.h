#pragma once

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QGraphicsTextItem>

class AI;
struct GameInfo;
class AbstractPlayer;
class InfoBanner;

class PlayerInfoContainer final: public QGraphicsObject {
    Q_OBJECT
public:
    PlayerInfoContainer(AbstractPlayer *player = nullptr);
    ~PlayerInfoContainer();

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;
};

class DashBoard final : public QGraphicsObject {
    Q_OBJECT
public:
    static DashBoard *getInstance();

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;
    ~DashBoard();
private:
    DashBoard();
};



class GameScene final : public QGraphicsScene
{
    Q_OBJECT

public:
    static GameScene *getInstance();
    ~GameScene();


    void prepareGame(const GameInfo &info);
    void run();

    inline int getCurrentLevel();

private:
    GameScene(QObject *parent);

    QList<PlayerInfoContainer *> ai_containers;

    InfoBanner* barner;
    DashBoard *dash_board;
};
