#include "gamelogic.h"
#include "bluemoon.h"
#include "player.h"
#include "card.h"

void GameLogic::start()
{
    if (game_scene == nullptr)
        return;
    if (current_player == nullptr)
        current_player = HumanPlayer::getInstance();
    while (this->alive_ais.length() > 0 && HumanPlayer::getInstance()->alive()) {
        // start round
        if (current_player->inherits("HumanPlayer")) {
            HumanPlayer::getInstance()->drawCard(4);
            for (auto &p : alive_ais) {
                
            }
            this->event_loop.exec();

        }
    }
}

GameLogic::GameLogic(QObject *parent)
    : QObject(parent), is_run(false),current_player(nullptr), game_scene(nullptr)
{
    QObject::connect(HumanPlayer::getInstance(), &HumanPlayer::endRound, &event_loop, &QEventLoop::quit);
    QObject::connect(HumanPlayer::getInstance(), &HumanPlayer::cardUsed, this, &GameLogic::playerUseCard);
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

void GameLogic::setGameScene(GameScene *scene)
{
    this->game_scene = scene;;
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

void GameLogic::damage(AbstractPlayer *from, AbstractPlayer *to, int n /*= 1*/)
{

}

void GameLogic::recover(AbstractPlayer *target, int n /*= 1*/)
{

}

AbstractPlayer * GameLogic::getNextAlive(AbstractPlayer *target)
{
    int idx = alive_players.indexOf(target);
    if (idx != -1) {
        return alive_players.at((idx + 1) % alive_players.length());
    }
}

void GameLogic::killPlayer(AbstractPlayer *player)
{

}

void GameLogic::useCardBy(AbstractPlayer *from, AbstractPlayer *to, Card *card)
{

}

void GameLogic::showAIPurpose(AI *ai)
{
    auto pur = ai->getCurrentOperation();
    for (auto &op : pur.keys()) {
        ai->addMark(ai->operaion2String(op), pur[op]);
    }
}

void GameLogic::executeAIOpreation(AI *ai)
{
    for (auto &mark : ai->getMarks()) {
        if (mark.startsWith("@")) {
            if (mark == "@attack") {
                damage(ai, HumanPlayer::getInstance(), ai->markNumber(mark));
                ai->removeMark(mark, ai->markNumber(mark));
            }   
        }
    }
}

void GameLogic::removeAIPurpose(AI *ai)
{

}

void GameLogic::playerUseCard(Card *card, AbstractPlayer *to)
{
    useCardBy(HumanPlayer::getInstance(), to, card);
}
