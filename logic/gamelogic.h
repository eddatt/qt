#pragma once

#include <QObject>
#include <QHash>
#include <QString>

class Skill;

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

class GameLogic : public QObject
{
    Q_OBJECT

public:
    static GameLogic *getInstance();
    ~GameLogic();

    QStringList getAllGenerals() const;

    void prepareGameScene(int level, const QStringList &ai_info);

    inline int currentLevel() const {
        return current_level;
    }

    QList<AI *> aliveAIs() const;
    QList<AbstractPlayer *> alivePlayers() const;

    static QHash<QString, General*> generals;

signals:
    void gameReady() const;

private:
    GameLogic(QObject *parent);
    int current_level;
    QList<AI *> alive_ais;
    QList<AbstractPlayer *> alive_players;

    bool is_run;
};
