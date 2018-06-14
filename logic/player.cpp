#include "player.h"



AbstractPlayer::AbstractPlayer()
    :m_general("ZhaZhaHui"), m_max_hp(100), m_hp(0)
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
    :m_magic(2),m_max_magic(2),m_power(1),m_agility(2),m_intelligence(3)
{

}
