#include "gamelogic.h"
#include "bluemoon.h"
#include "player.h"
#include "card.h"
#include "ui/dash_board.h"
#include "ui/gamescene.h"

#include <QTimer>

void GameLogic::startGame()
{
    if (game_scene == nullptr)
        return;
    if (current_player == nullptr) {
        current_player = HumanPlayer::getInstance();
    }
    current_player->removeMark("@defense", current_player->markNumber("@defense"));
    for(auto &p :alive_ais)
        showAIPurpose(p);
    HumanPlayer::getInstance()->setMagic(HumanPlayer::getInstance()->maxMagic());
    HumanPlayer::getInstance()->drawCard(4);
    
}

void GameLogic::newRound()
{
    if (!is_run) return;
    HumanPlayer::getInstance()->discardWholeHandcard();
    HumanPlayer::getInstance()->setDrunk(0);
    HumanPlayer::getInstance()->setCurrent(false);
    current_player = getNextAlive(current_player);
    current_player->setCurrent(true);
    while (current_player != HumanPlayer::getInstance() && this->alive_ais.length() > 0 && HumanPlayer::getInstance()->alive()) {
        current_player->setCurrent(true);
        current_player->removeMark("@defense", current_player->markNumber("@defense"));
        // A
        AI *ai = qobject_cast<AI *>(current_player);
        executeAIOpreation(ai);
        removeAIPurpose(ai);
        current_player->setCurrent(false);
        current_player = getNextAlive(current_player);
    }
    current_player = HumanPlayer::getInstance();
    current_player->setCurrent(true);
    for (auto &p : alive_ais)
        showAIPurpose(p);
    current_player->removeMark("@defense", current_player->markNumber("@defense"));
    HumanPlayer::getInstance()->setMagic(HumanPlayer::getInstance()->maxMagic());
    HumanPlayer::getInstance()->drawCard(4);

}

GameLogic::GameLogic(QObject *parent)
    : QObject(parent), is_run(false),current_player(nullptr), game_scene(nullptr)
{
	General a, b, c;
	a.name = "ZhaZhaHui";
	a.max_hp = 80;
	a.pwr_plus = 0;
	a.agility_plus = 0;
	a.intelligence_plus = 0;

	b.name = "GuTianLe";
	b.max_hp = 70;
	b.pwr_plus = 0;
	b.agility_plus = 0;
	b.intelligence_plus = 0;

	c.name = "ChenXiaoChun";
	c.max_hp = 60;
	c.pwr_plus = 0;
	c.agility_plus = 0;
	c.intelligence_plus = 1;

	this->generals["ZhaZhaHui"] = a;
    this->generals["GuTianLe"] = b;
    this->generals["ChenXiaoChun"] = c;


    QObject::connect(HumanPlayer::getInstance(), &HumanPlayer::endRound, this, &GameLogic::newRound);
    QObject::connect(HumanPlayer::getInstance(), &HumanPlayer::cardUsed, this, &GameLogic::playerUseCard);

    alive_players << HumanPlayer::getInstance();

}

void GameLogic::freeGarbage()
{
    for (auto &p : garbage) {
        delete p;
    }
    garbage.clear();
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
    this->game_scene = scene;
    if (scene == nullptr) {
        is_run = false;
        alive_ais.clear();
        alive_players.clear();
        current_player = nullptr;
        current_level = 0;
    }
}

void GameLogic::prepareGameScene(int level)
{
    current_level = level;
    if (level > LEVEL_NUMBER) {
        emit allLevelFinished();
        return;
    }
	QList<int> l;
	if (level == 1) {
		l.push_back(0);
	}
	else if (level == 2) {
		l.push_back(1);
		l.push_back(4);
	}
	else if (level == 3) {
		l.push_back(2);
		l.push_back(4);
	}
	else if (level == 4) {
		l.push_back(3);
		l.push_back(3);
		l.push_back(5);
	}
	else if (level == 5) {
		l.push_back(6);
		l.push_back(3);
		l.push_back(5);
	}
    for (auto &p : alive_ais) {
        delete p;
    }
    alive_ais.clear();
    this->current_level = level;
    for (auto &c : l) {
        auto nai = new AI(c);
        alive_ais << nai;
        alive_players << nai;
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
    //deal defense
    if (to->markNumber("@defense") >= n) {
        to->removeMark("@defense", n);
        return;
    }
    n -= to->markNumber("@defense");
    to->removeMark("@defense", to->markNumber("@defense"));
    int new_hp = qMax<int>(to->hp() - n,0);
    to->setHp(new_hp);
    if (new_hp == 0) {
        killPlayer(to);
    }
}

void GameLogic::recover(AbstractPlayer *target, int n /*= 1*/)
{
    int loseHp = target->maxHp() - target->hp();
    if (loseHp == 0)
        return;
    n = qMin<int>(n, loseHp);
    target->setHp(target->hp() + n);
}

AbstractPlayer * GameLogic::getNextAlive(AbstractPlayer *target)
{
    int idx = alive_players.indexOf(target);
    if (idx != -1) {
        return alive_players.at((idx + 1) % alive_players.length());
    }
    return nullptr;
}

void GameLogic::killPlayer(AbstractPlayer *player)
{
    player->setAlive(false);
    alive_players.removeAll(player);
    for (auto &m : player->getMarks()) {
        player->removeMark(m, player->markNumber(m));
    }
    if (player->inherits("AI")) {
        alive_ais.removeAll(qobject_cast<AI *>(player));
    }
    else {
        // Human died
        HumanPlayer::getInstance()->discardWholeHandcard();
        is_run = false;
        emit gameFinished(false);
    }
    if (alive_ais.length() == 0) {
        HumanPlayer::getInstance()->discardWholeHandcard();
        is_run = false;
        emit gameFinished(true);
    }
}

void GameLogic::useCardBy(AbstractPlayer *from, AbstractPlayer *to, Card *card)
{
    // remove Magic
    if (from->inherits("HumanPlayer")) {
        HumanPlayer::getInstance()->setMagic(HumanPlayer::getInstance()->magic() - card->energy());
    }
    card->doEffect(to);
    HumanPlayer::getInstance()->discardOneCard(card);
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
            else if (mark == "@enhance") {
                ai->removeMark(mark, ai->markNumber(mark));
            }
        }
    }
}

void GameLogic::removeAIPurpose(AI *ai)
{
    for (auto &mark : ai->getMarks()) {
        if (mark.startsWith("@")) {
            ai->removeMark(mark, ai->markNumber(mark));
        }
    }
}

void GameLogic::drawCard(int n)
{
    QList<CardItem *> items;
    for (int i = 0; i < n; ++i) {
        auto c = Card::generateCard();
        items << c->cardItem();
        HumanPlayer::getInstance()->addCard(c);
    }
    game_scene->dashBoard()->addCardItems(items);
}

void GameLogic::discard(Card * card)
{
    HumanPlayer::getInstance()->removeCard(card);
    game_scene->dashBoard()->removeCardItem(card->cardItem());
}

void GameLogic::discardAllCard()
{
    HumanPlayer::getInstance()->removeAllCard();
    game_scene->dashBoard()->removeAllCardItem();
}

void GameLogic::addGeneral(const QString & name, General general)
{
    generals[name] = general;
}

General GameLogic::generalInfo(const QString & name)
{
    return generals[name];
}

void GameLogic::playerUseCard(Card *card, AbstractPlayer *to)
{
    useCardBy(HumanPlayer::getInstance(), to, card);
}
