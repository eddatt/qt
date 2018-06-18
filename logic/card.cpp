#include "card.h"
#include "ui/carditem.h"
#include "player.h"
#include "gamelogic.h"
#include <random>

std::random_device rd;


Card::Card(const QString &xn)
    :m_name(xn)
{
    item = new CardItem(this);
}


Card::~Card()
{
    delete item;
}

bool Card::isAvailable() const
{
    int e=HumanPlayer::getInstance()->magic();
    return e>=m_energy;
}


CardItem * Card::cardItem() const
{
    return item;
}

QString Card::name() const
{
    return m_name;
}

bool Card::targetFix() const
{
    return false;
}

bool Card::filterTarget(AbstractPlayer *target) const
{
    return target->alive();
}

void Card::doEffect(AbstractPlayer *target)
{
    return;
}

Card * Card::generateCard()
{
	int a = rd() % 30;
	if (a < 7) {
		return new Kill;
	}
	else if (a < 14) {
		return new Jink;
	}
	else if (a < 18) {
		return new Wine;
	}
	else if (a < 22) {
		return new Songjian;
	}
	else if (a < 23) {
		return new Shengnu;
	}
	else if (a < 25) {
		return new Zhongji;
	}
	else if (a < 26) {
		return new Xianji;
	}
	else if (a < 27) {
		return new Peach;
	}
	else if (a < 28) {
		return new Maifu;
	}
	else {
		return new Guisuo;
	}
}

int Card::energy() const
{
	return m_energy;
}

void Card::setEnergy(int e)
{
	m_energy = e;
}

Kill::Kill()
	:Card("kill")
{
	m_energy = 1;
}

bool Kill::targetFix() const
{
	return false;
}

bool Kill::filterTarget(AbstractPlayer * target) const
{
	return target->alive();
}

void Kill::doEffect(AbstractPlayer * target)
{
	GameLogic::getInstance()->damage(HumanPlayer::getInstance(), target, (6 + HumanPlayer::getInstance()->power() * 2)*(1 + HumanPlayer::getInstance()->drunk()));
}

Jink::Jink()
	:Card("jink")
{
	m_energy = 1;
}

bool Jink::targetFix() const
{
	return true;
}

bool Jink::filterTarget(AbstractPlayer * target) const
{
	return false;
}

void Jink::doEffect(AbstractPlayer * target)
{
	HumanPlayer::getInstance()->addMark("@defense", 5 + HumanPlayer::getInstance()->agility() * 2);
}

Wine::Wine()
	:Card("wine")
{
	m_energy = 1;
}

bool Wine::targetFix() const
{
	return true;
}

bool Wine::filterTarget(AbstractPlayer * target) const
{
	return false;
}

void Wine::doEffect(AbstractPlayer * target)
{
	HumanPlayer::getInstance()->setDrunk();
}

Peach::Peach()
	:Card("peach")
{
	m_energy = 2;
}

bool Peach::targetFix() const
{
	return true;
}

bool Peach::filterTarget(AbstractPlayer * target) const
{
	return false;
}

void Peach::doEffect(AbstractPlayer * target)
{
	GameLogic::getInstance()->recover(HumanPlayer::getInstance(), 10);
}

bool Peach::isAvailable() const
{
    return HumanPlayer::getInstance()->maxHp() - HumanPlayer::getInstance()->hp() > 0 && Card::isAvailable();
}

Guisuo::Guisuo()
	:Card("guisuo")
{
	m_energy = 2;
}

bool Guisuo::targetFix() const
{
	return true;
}

bool Guisuo::filterTarget(AbstractPlayer * target) const
{
	return false;
}

void Guisuo::doEffect(AbstractPlayer * target)
{
	HumanPlayer::getInstance()->addMark("@defense", 25 + HumanPlayer::getInstance()->agility() * 2);
}

Maifu::Maifu()
	:Card("maifu")
{
	m_energy = 1;
}

bool Maifu::targetFix() const
{
	return false;
}

bool Maifu::filterTarget(AbstractPlayer * target) const
{
	return target->alive();
}

void Maifu::doEffect(AbstractPlayer * target)
{
	GameLogic::getInstance()->damage(HumanPlayer::getInstance(), target, (10 + HumanPlayer::getInstance()->power() * 2)*(1 + HumanPlayer::getInstance()->drunk()));
}

Songjian::Songjian()
	:Card("songjian")
{
	m_energy = 1;
}

bool Songjian::targetFix() const
{
	return true;
}

bool Songjian::filterTarget(AbstractPlayer * target) const
{
	return false;
}

void Songjian::doEffect(AbstractPlayer * target)
{
	HumanPlayer::getInstance()->addMark("@defense", 8 + HumanPlayer::getInstance()->agility() * 2);
}

Shengnu::Shengnu()
	:Card("shengnu")
{
	m_energy = 1;
}

bool Shengnu::targetFix() const
{
	return true;
}

bool Shengnu::filterTarget(AbstractPlayer * target) const
{
	return false;
}

void Shengnu::doEffect(AbstractPlayer * target)
{
	HumanPlayer::getInstance()->setMagic(HumanPlayer::getInstance()->magic() + 2);
}

Xianji::Xianji()
	:Card("xianji")
{
	m_energy = 0;
}

bool Xianji::targetFix() const
{
	return false;
}

bool Xianji::filterTarget(AbstractPlayer * target) const
{
	return target->alive();
}

void Xianji::doEffect(AbstractPlayer * target)
{
	GameLogic::getInstance()->damage(HumanPlayer::getInstance(), target, (20 + HumanPlayer::getInstance()->power() * 2)*(1 + HumanPlayer::getInstance()->drunk()));
	GameLogic::getInstance()->damage(target, HumanPlayer::getInstance(), (20 + HumanPlayer::getInstance()->power() * 2)*(1 + HumanPlayer::getInstance()->drunk()));
}

Zhongji::Zhongji()
	:Card("zhongji")
{
	m_energy = 2;
}

bool Zhongji::targetFix() const
{
	return false;
}

bool Zhongji::filterTarget(AbstractPlayer * target) const
{
	return target->alive();
}

void Zhongji::doEffect(AbstractPlayer * target)
{
	GameLogic::getInstance()->damage(HumanPlayer::getInstance(), target, (20 + HumanPlayer::getInstance()->power() * 2)*(1 + HumanPlayer::getInstance()->drunk()));
}
