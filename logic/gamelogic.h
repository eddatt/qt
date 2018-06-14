#pragma once

#include <QObject>
#include <QHash>
#include <QString>

class Skill;

struct General {
    QString name;
    QList<Skill *> skills;
    int max_hp;
    int pwr_plus;
    int agility_plus;
    int intelligence_plus;
};

struct GameInfo {
    int level;
    QList<General *> ais;
};

class GameLogic : public QObject
{
    Q_OBJECT

public:
    static GameLogic *getInstance();
    ~GameLogic();

    QStringList getAllGenerals() const;

    void prepareGameScene(const GameInfo &info) const;

    inline int currentLevel() const {
        return current_info.level;
    }

private:
    GameLogic(QObject *parent);
    QHash<QString, General*> generals;

    GameInfo current_info;


    bool is_run;
};
