#pragma once
#include <QObject>
#include <QHash>
#include <QString>

class Skill;
class Item;
class Card;

class AbstractPlayer : public QObject
{
    Q_OBJECT
public:
    AbstractPlayer();
    virtual ~AbstractPlayer();

    inline int hp() const {
        return this->m_hp;
    }
    void setHp(int new_hp) {
        this->m_hp = new_hp;
        hpChanged();
    }
    inline int maxHp() const {
        return this->m_max_hp;
    }
    void setMaxHp(int new_max_hp) {
        this->m_max_hp = new_max_hp;
        maxHpChanged();
    }
    inline QString general() const {
        return m_general;
    }
    void setGeneral(const QString &general) {
        this->m_general = general;
        generalChanged();
    }
    QStringList getMarks() const {
        return marks.keys();
    }
    int markNumber(const QString &mark) {
        return marks[mark];
    }
signals:
    void hpChanged();
    void maxHpChanged();
    void generalChanged();

protected:
    QString m_general;
    int m_max_hp;
    int m_hp;
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

    inline int magic() const {
        return m_magic;
    }
    void setMagic(int mg) {
        mg = qMax<int>(mg, m_max_magic);
        this->m_magic = mg;
        magicChanged();
    }
    inline int maxMagic() const {
        return m_max_magic;
    }
    void setMaxMagic(int mmg) {
        this->m_max_magic = mmg;
        maxMagicChanged();
    }
    inline int power() const {
        return m_power;
    }
    void setPower(int power) {
        this->m_power = power;
        powerChanged();
    }
    inline int agility() const {
        return m_agility;
    }
    void setAgility(int ag) {
        this->m_agility = ag;
        agilityChanged();
    }
    inline int intelligence() const {
        return m_intelligence;
    }
    void setIntelligence(int intel) {
        this->m_intelligence = intel;
        intelligenceChanged();
    }
    inline const QList<Item *> &items() {
        return m_items;
    };
signals:
    void magicChanged();
    void maxMagicChanged();
    void powerChanged();
    void agilityChanged();
    void intelligenceChanged();
private:
    HumanPlayer();
    int m_magic;
    int m_max_magic;

    int m_power;
    int m_agility;
    int m_intelligence;

    QList<Item *> m_items;

    QList<Card *> cards;
};

