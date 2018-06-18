#include "player.h"
#include "item.h"
#include "card.h"
#include "gamelogic.h"

#include <QMap>
#include <random>

extern std::random_device rd;

int pow(int i, double x, int ori) {
	double re = 1.0;
	for (int j = 0; j < i; j++) {
		re *= x;
	}
	return (int)(re*ori);
}

AbstractPlayer::AbstractPlayer()
    :m_general("ZhaZhaHui"), m_max_hp(100), m_hp(m_max_hp)
{

}


AbstractPlayer::~AbstractPlayer()
{

}

void AbstractPlayer::setGeneral(const QString &general)
{
    this->m_general = general;
    generalChanged();
	setMaxHp(GameLogic::getInstance()->generalInfo(general).max_hp);
	setHp(GameLogic::getInstance()->generalInfo(general).max_hp);
    //setMaxHp()
}

void AbstractPlayer::addMark(const QString &mark, int n /*= 1*/)
{
    marks[mark] += n;
    MarkChanged(mark);
}

void AbstractPlayer::removeMark(const QString &mark, int n /*= 1*/)
{
    n = qMin<int>(n, marks[mark]);
    if (n == marks[mark])
        marks.remove(mark);
    else {
        marks[mark] -= n;
    }
    MarkChanged(mark);
}

HumanPlayer * HumanPlayer::getInstance()
{
    static HumanPlayer player;
    return &player;
}

HumanPlayer::~HumanPlayer()
{

}

void HumanPlayer::setGeneral(const QString & name)
{

	HumanPlayer::setAgility(GameLogic::getInstance()->generalInfo(name).agility_plus);
	HumanPlayer::setPower(GameLogic::getInstance()->generalInfo(name).pwr_plus);
	HumanPlayer::setIntelligence(GameLogic::getInstance()->generalInfo(name).intelligence_plus);
	AbstractPlayer::setGeneral(name);
    this->setAlive(true);
}

void HumanPlayer::drawCard(int n)
{
    GameLogic::getInstance()->drawCard(n);
}

void HumanPlayer::discardWholeHandcard()
{
    GameLogic::getInstance()->discardAllCard();
}

void HumanPlayer::discardOneCard(Card *card)
{
    GameLogic::getInstance()->discard(card);
}

HumanPlayer::HumanPlayer()
    :m_magic(2),m_max_magic(2),m_power(0),m_agility(0),m_intelligence(0)
{
	 
}

AI::AI(int i)
{
	if (i == 0) {
		m_name = "m1";
		m_hp = 60;
		m_max_hp = 60;
		for (int j = 0; j < 100; j++) {
			attacks.push_back(5 + rd() % 2);
			defends.push_back(0 + rd() % 2);
			//statuss.push_back(0);
		}
	}
	else if (i == 1) {
		m_name = "m2";
		m_hp = 40;
		m_max_hp = 40;
		attacks.push_back(4 + rd() % 2);
		attacks.push_back(0 + rd() % 2);
		attacks.push_back(4 + rd() % 2);
		attacks.push_back(0 + rd() % 2);
		attacks.push_back(0 + rd() % 2);

		defends.push_back(0 + rd() % 2);
		defends.push_back(5 + rd() % 2);
		defends.push_back(0 + rd() % 2);
		defends.push_back(5 + rd() % 2);
		defends.push_back(0 + rd() % 2);

		//statuss.push_back(0);
		//statuss.push_back(0);
		//statuss.push_back(0);
		//statuss.push_back(0);
		//statuss.push_back(1);

		for (int j = 5; j < 100; j++) {
			if (j % 2) {
				attacks.push_back(6 + rd() % 3);
				defends.push_back(0 + rd() % 3);
			}
			else {
				attacks.push_back(0 + rd() % 3);
				defends.push_back(8 + rd() % 3);
			}
			//statuss.push_back(0);
		}
	}
	else if (i == 2) {
		m_name = "m3";
		m_hp = 50;
		m_max_hp = 50;
		attacks.push_back(6 + rd() % 2);
		attacks.push_back(0 + rd() % 2);
		attacks.push_back(6 + rd() % 2);
		attacks.push_back(0 + rd() % 2);
		attacks.push_back(0 + rd() % 2);

		defends.push_back(0 + rd() % 2);
		defends.push_back(8 + rd() % 2);
		defends.push_back(0 + rd() % 2);
		defends.push_back(8 + rd() % 2);
		defends.push_back(0 + rd() % 2);

		//statuss.push_back(0);
		//statuss.push_back(0);
		//statuss.push_back(0);
		//statuss.push_back(0);
		//statuss.push_back(1);

		for (int j = 5; j < 100; j++) {
			if (j % 2) {
				attacks.push_back(8 + rd() % 3);
				defends.push_back(0 + rd() % 5);
			}
			else {
				attacks.push_back(0 + rd() % 5);
				defends.push_back(12 + rd() % 3);
			}
			//statuss.push_back(0);
		}
	}
	else if (i == 3) {
		m_name = "m4";
		m_hp = 10;
		m_max_hp = 10;
		for (int j = 0; j < 100; j++) {
			if (j % 2) {
				attacks.push_back(5 + rd() % 3);
				defends.push_back(20 + rd() % 3);
			}
			else {
				attacks.push_back(0 + rd() % 3);
				defends.push_back(30 + rd() % 3);
			}
			//statuss.push_back(0);
		}
	}
	else if (i == 4) {
		m_name = "m5";
		m_hp = 30;
		m_max_hp = 30;
		for (int j = 0; j < 100; j++) {
			if (j % 3 != 2) {
				attacks.push_back(2 + rd() % 3);
				defends.push_back(5 + rd() % 3);
			}
			else {
				attacks.push_back(3 + rd() % 3);
				defends.push_back(5 + rd() % 3);
			}
			//statuss.push_back(0);
		}
	}
	else if (i == 5) {
		m_name = "m6";
		m_hp = 20;
		m_max_hp = 20;
		for (int j = 0; j < 100; j++) {
			if (j % 3 != 2) {
				attacks.push_back(3 + rd() % 4);
				defends.push_back(6 + rd() % 4);
			}
			else {
				attacks.push_back(10 + rd() % 4);
				defends.push_back(3 + rd() % 4);
			}
			//statuss.push_back(0);
		}
	}
	else {
		m_name = "boss";
		m_hp = 100;
		m_max_hp = 100;
		for (int j = 0; j < 100; j++) {
			if (j % 6 == 0) {
				attacks.push_back(pow((j - j % 6) / 6, 1.5, 14) + rd() % 4 - 2);
				defends.push_back(0 + rd() % 4);
				//statuss.push_back(0);
			}
			if (j % 6 == 1) {
				attacks.push_back(pow((j - j % 6) / 6, 1.5, 4) + rd() % 4 - 2);
				defends.push_back(0 + rd() % 4);
				//statuss.push_back(0);
			}
			if (j % 6 == 2) {
				attacks.push_back(pow((j - j % 6) / 6, 1.5, 4) + rd() % 4 - 2);
				defends.push_back(0 + rd() % 4);
				//statuss.push_back(0);
			}
			if (j % 6 == 3) {
				attacks.push_back(pow((j - j % 6) / 6, 1.5, 4) + rd() % 4 - 2);
				defends.push_back(0 + rd() % 4);
				//statuss.push_back(0);
			}
			if (j % 6 == 4) {
				attacks.push_back(0);
				defends.push_back(0);
				//statuss.push_back(1);
			}
			if (j % 6 == 5) {
				attacks.push_back(0);
				defends.push_back(0);
				//statuss.push_back(1);
			}
		}
	}
	setGeneral(m_name);
}

AI::~AI()
{

}

QString AI::general() const
{
    return m_name;
}

void AI::setGeneral(const QString &)
{
	emit generalChanged();
}

QMap<AI::Operation, int> AI::getCurrentOperation() const
{
	int k = rd() % 100;
	QMap<AI::Operation, int> map;
	map[Operation::Attack] = attacks[k];
	map[Operation::Defense] = defends[k];
    return map;
}

QString AI::operaion2String(Operation o)
{
    switch (o) {
    case Operation::Attack:
        return "@attack";
    case Operation::Defense:
        return "@defense";  
    }
    return "";
}

