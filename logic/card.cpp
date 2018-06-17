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

bool Card::isAvailable(AbstractPlayer *player) const
{
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

void Card::doEffect(AbstractPlayer *self, AbstractPlayer *target)
{
    return;
}
