#include "card.h"
#include "ui/carditem.h"
#include "player.h"
#include "gamelogic.h"




Card::Card(const QString &xn)
    :m_name(xn)
{
    item = new CardItem(this);
}


Card::~Card()
{
    
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
	return true;
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
	return false;
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
	return false;
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
	return false;
}

bool Peach::filterTarget(AbstractPlayer * target) const
{
	return false;
}

void Peach::doEffect(AbstractPlayer * target)
{
	GameLogic::getInstance()->recover(HumanPlayer::getInstance(), 10);
}

Guisuo::Guisuo()
	:Card("guisuo")
{
	m_energy = 2;
}

bool Guisuo::targetFix() const
{
	return false;
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
	return true;
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
	return false;
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
	return false;
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
	return true;
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
	return true;
}

bool Zhongji::filterTarget(AbstractPlayer * target) const
{
	return target->alive();
}

void Zhongji::doEffect(AbstractPlayer * target)
{
	GameLogic::getInstance()->damage(HumanPlayer::getInstance(), target, (20 + HumanPlayer::getInstance()->power() * 2)*(1 + HumanPlayer::getInstance()->drunk()));
}
