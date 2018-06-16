#include "player.h"
#include "item.h"



AbstractPlayer::AbstractPlayer()
    :m_general("ZhaZhaHui"), m_max_hp(100), m_hp(m_max_hp)
{
}


AbstractPlayer::~AbstractPlayer()
{

}

HumanPlayer * HumanPlayer::getInstance()
{
    static HumanPlayer player;
    return &player;
}

HumanPlayer::~HumanPlayer()
{

}

HumanPlayer::HumanPlayer()
    :m_magic(2),m_max_magic(2),m_power(0),m_agility(0),m_intelligence(0)
{

}
