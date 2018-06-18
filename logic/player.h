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
    void setGeneral(const QString &general);
    QStringList getMarks() const {
        return marks.keys();
    }
    int markNumber(const QString &mark) {
        return marks[mark];
    }
    inline bool alive() const {
        return m_alive;
    }
    void setAlive(bool alive) {
        this->m_alive = alive;
        emit aliveChanged(alive);
    }
    void addMark(const QString &mark, int n = 1);
    void removeMark(const QString &mark, int n = 1);

    void setCurrent(bool is_cur) {
        is_current = is_cur;
        currentChanged(is_cur);
    }
signals:
    void hpChanged();
    void maxHpChanged();
    void generalChanged();
    void aliveChanged(bool);
    void MarkChanged(QString);
    void currentChanged(bool);
protected:
    QString m_general;
    bool m_alive;
    int m_max_hp;
    int m_hp;
    QList<Skill *> skills;
    QHash<QString, int> marks;
    bool is_current;
};

class AI : public AbstractPlayer
{
    Q_OBJECT
public:
    AI(int i);
    virtual ~AI();
    enum class Operation {
        Attack, Defense
    };

    QMap<AI::Operation,int> getCurrentOperation() const;

    static QString operaion2String(AI::Operation);


private:
    int enhanced_point;
	QString m_name;
	QList<int> attacks;
	QList<int> defends;
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
	inline int drunk() const {
		return m_drunk;
	}
	void setDrunk() {
		this->m_drunk = 1;
	}
    inline const QList<Item *> &items() {
        return m_items;
    };

    inline const QList<Card *> &cards() {
        return m_cards;
    }

    void drawCard(int n);
    void discardWholeHandcard();
    void discardOneCard(Card *card);
signals:
    void magicChanged();
    void maxMagicChanged();
    void powerChanged();
    void agilityChanged();
    void intelligenceChanged();

    void endRound();
    void cardUsed(Card *card, AbstractPlayer *target);
private:
    HumanPlayer();
    int m_magic;
    int m_max_magic;

    int m_power;
    int m_agility;
    int m_intelligence;
	int m_drunk = 0;

    QList<Item *> m_items;

    QList<Card *> m_cards;
};

