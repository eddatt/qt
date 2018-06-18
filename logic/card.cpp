#include "card.h"
#include "ui/carditem.h"



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
    //HumanPlayer::getInstance();
    return false;
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
    return false;
}

void Card::doEffect(AbstractPlayer *self, AbstractPlayer *target)
{
    return;
}
