#pragma once
#include <QObject>
#include <QHash>
#include <QString>

class Skill;
class Item;

class AbstractPlayer : public QObject
{
    Q_OBJECT
public:
    AbstractPlayer();
    virtual ~AbstractPlayer();

private:
    int max_hp;
    int hp;
    QList<Skill *> skills;
    QHash<QString, int> marks;
};

class AI : public AbstractPlayer
{
    Q_OBJECT
public:
    AI();
    virtual ~AI();

};

class HumanPlayer : public AbstractPlayer
{
    Q_OBJECT
public:
    static HumanPlayer *getInstance();
    virtual ~HumanPlayer();
private:
    HumanPlayer();
    int magic;

    QList<Item *> items;
};

