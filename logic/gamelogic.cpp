#include "gamelogic.h"
#include "bluemoon.h"
#include "player.h"

GameLogic::GameLogic(QObject *parent)
    : QObject(parent), is_run(false)
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

void GameLogic::prepareGameScene(int level, const QStringList &ai_info)
{
    for (auto &p : alive_ais) {
        delete p;
    }
    alive_ais.clear();
    this->current_level = level;
    for (auto &c : ai_info) {
        auto nai = new AI();
        nai->setGeneral(c);
        alive_ais << nai;
    }
    emit gameReady();
}

QList<AI *> GameLogic::aliveAIs() const
{
    return alive_ais;
}

QList<AbstractPlayer *> GameLogic::alivePlayers() const
{
    return alive_players;
}
