#include "card.h"
#include "ui/carditem.h"
#include "player.h"




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
	target->setHp(target->hp() - (6 + HumanPlayer::getInstance()->power() * 2)*(1 + HumanPlayer::getInstance()->drunk()));
}

Jink::Jink()
	:Card("jink")
{
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
	HumanPlayer::getInstance()->addMark("@defense",5+HumanPlayer::getInstance()->agility()*2)
}

Wine::Wine()
	:Card("wine")
{
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
