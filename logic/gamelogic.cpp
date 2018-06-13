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

QStringList GameLogic::getAllGenerals() const
{
    //return this->generals.keys();
    // will be done in Lua.
    QStringList l = { "ZhaZhaHui","GuTianLe","ChenXiaoChun" };
    return l;
}
