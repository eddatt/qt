#include "gamelogic.h"
#include "bluemoon.h"

GameLogic::GameLogic(QObject *parent)
    : QObject(parent)
{
}

GameLogic * GameLogic::getInstance()
{
    static GameLogic logic(nullptr);
    return &logic;
}

GameLogic::~GameLogic()
{
}
