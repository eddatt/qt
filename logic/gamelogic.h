#pragma once

#include <QObject>
#include <QHash>
#include <QString>

class Skill;

struct General {
    QString name;
    QList<Skill *> skills;
};

class GameLogic : public QObject
{
    Q_OBJECT

public:
    static GameLogic *getInstance();
    ~GameLogic();

private:
    GameLogic(QObject *parent);
    QHash<QString, General*> generals;
};
