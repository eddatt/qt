#pragma once

#include <QObject>
#include <QHash>
#include <QString>
#include <QMap>
#include <QEventLoop>
#include <QThread>

class Skill;
class GameScene;
class Card;

struct General {
    QString name;
    //QList<Skill *> skills;
    int max_hp;
    int pwr_plus;
    int agility_plus;
    int intelligence_plus;
};

class AbstractPlayer;
class AI;

class GameLogic : public QThread
{
    Q_OBJECT

public:
    static GameLogic *getInstance();
    ~GameLogic();

    QStringList getAllGenerals() const;

    void setGameScene(GameScene *scene);

    void prepareGameScene(int level);

    inline int currentLevel() const {
        return current_level;
    }

    QList<AI *> aliveAIs() const;
    QList<AbstractPlayer *> alivePlayers() const;

    void damage(AbstractPlayer *from, AbstractPlayer *to, int n = 1);
    void recover(AbstractPlayer *target, int n = 1);

    AbstractPlayer *getNextAlive(AbstractPlayer *target);

    void killPlayer(AbstractPlayer *player);

    void useCardBy(AbstractPlayer *from, AbstractPlayer *to, Card *card);

    void showAIPurpose(AI *ai);
    void executeAIOpreation(AI *ai);
    void removeAIPurpose(AI *ai);

    void drawCard(int n = 1);
    void discard(Card *card);
    void discardAllCard();

    void addGeneral(const QString &name, General general);
    General generalInfo(const QString &name);

    const static int LEVEL_NUMBER = 5;


public slots:
    void startGame();

    void newRound();

    void playerUseCard(Card *card, AbstractPlayer *to);

signals:
    void gameReady() const;
    void gameFinished(bool win);
    void allLevelFinished();

private:
    GameLogic(QObject *parent);

    void freeGarbage();
    int current_level;
    QList<AI *> alive_ais;
    QList<AbstractPlayer *> alive_players;

    QMap<int, QStringList> level_info;

    bool is_run;

    QEventLoop event_loop;
    AbstractPlayer *current_player;

    GameScene *game_scene;

    QList<Card *> garbage;

    QMap<QString, General> generals;
};
