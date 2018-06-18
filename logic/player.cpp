#include "player.h"
#include "item.h"
#include "card.h"
#include <QMap>



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
    //setMaxHp()
}

void AbstractPlayer::addMark(const QString &mark, int n /*= 1*/)
{
    marks[mark] += n;
}

void AbstractPlayer::removeMark(const QString &mark, int n /*= 1*/)
{
    n = qMin<int>(n, marks[mark]);
    if (n == marks[mark])
        marks.remove(mark);
    else {
        marks[mark] -= n;
    }
}

HumanPlayer * HumanPlayer::getInstance()
{
    static HumanPlayer player;
    return &player;
}

HumanPlayer::~HumanPlayer()
{

}

void HumanPlayer::drawCard(int n)
{

}

void HumanPlayer::discardWholeHandcard()
{

}

void HumanPlayer::discardOneCard(Card *card)
{

}

HumanPlayer::HumanPlayer()
    :m_magic(2),m_max_magic(2),m_power(0),m_agility(0),m_intelligence(0)
{

}

AI::AI()
{

}

AI::~AI()
{

}

QMap<AI::Opreation, int> AI::getCurrentOperation() const
{
    return QMap<AI::Opreation, int>();
}

QString AI::operaion2String(Opreation o)
{
    switch (o) {
    case Opreation::Attack: 
        return "@attack";
    
    case Opreation::Defense :
        return "@defense";
    
    case Opreation::Enhance :
        return "@enhance";
    }
    return "";
}

void AI::setEnhanced(int power)
{
    this->enhanced_point = power;
}

int AI::enhancedPoint() const
{
    return enhanced_point;
}
