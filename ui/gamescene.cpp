#include "gamescene.h"
#include "logic/player.h"
#include "logic/gamelogic.h"
#include "uiutility.h"
#include "infobarner.h"
#include "dash_board.h"
#include "PlayerAvatarContainer.h"
#include "carditem.h"
#include "logic/card.h"
#include "button.h"
#include "bluemoon.h"
#include "startscene.h"

#include <QPixmap>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

GameScene::GameScene(QObject *parent)
    :QGraphicsScene(parent), is_prepared(false)
{
    setSceneRect(UIUtility::getGraphicsSceneRect());
    dash_board = new DashBoard;
    dash_board->setParent(this);
    this->addItem(dash_board);
    dash_board->setPos(0, UIUtility::getGraphicsSceneRect().height() - dash_board->boundingRect().height());
    dash_board->show();

    QObject::connect(dash_board->cardItemManager(), &CardItemManager::selectChanged,this,&GameScene::prepareFortargetSelect);

    barner = new InfoBanner;
    barner->setParent(this);
    this->addItem(barner);
    barner->setPos(0, 0);
    barner->show();
    this->setBackgroundBrush(QPixmap(UIUtility::getBackgroundPath("on_game")));

    GameLogic::getInstance()->setGameScene(this);
    QObject::connect(GameLogic::getInstance(), &GameLogic::gameReady, this, &GameScene::prepareGame);
    QObject::connect(GameLogic::getInstance(), &GameLogic::gameFinished, this, &GameScene::onGameFinished);

    win = new GameFinishPrompt(true);
    lose = new GameFinishPrompt(false);
    win->setParent(this);
    win->setPos(width() / 2 - win->boundingRect().width() / 2, height() / 2 - win->boundingRect().height() / 2);
    lose->setParent(this);
    lose->setPos(width() / 2 - lose->boundingRect().width() / 2, height() / 2 - lose->boundingRect().height() / 2);
    this->addItem(win);
    this->addItem(lose);

    win->hide();
    //lose->hide();
}


/*
__________________________________________________________________________
General Name   Hp             Property                           Cards            
__________________________________________________________________________
Items
__________________________________________________________________________



     _____________                                       _____________
    |             |                                     |             |
    |             |                                     |             |
    |             |                                     |             |
    |             |                                     |             |
    |             |                                     |             |
    |             |                                     |             |
    |_____________|                                     |_____________|
    |             |                                     |             |
    |_____________|                                     |_____________|


__________________                                 _____________
Effect and Marks                                  |    Magic    |
__________________________________________________|_____________|_____________
DashBoard                                                    |            |   |
                                                             |            | H |
                                                             |            |   |
                                                             |   Avatar   |   |
                                                             |            |   |
                                                             |            | P |
_____________________________________________________________|____________|___|

*/

GameScene::~GameScene()
{
       
}

int GameScene::getCurrentLevel()
{
    return GameLogic::getInstance()->currentLevel();
}

void GameScene::prepareGame()
{
    barner->updateLevel(GameLogic::getInstance()->currentLevel());
    createAIContainer();
    is_prepared = true;
    run();
}

void GameScene::createAIContainer()
{
    for (auto &p : ai_containers) {
        p->hide();
        p->setParentItem(nullptr);
    }
    ai_containers.clear();

    double cy = barner->boundingRect().height() + (height() - barner->boundingRect().height() - dash_board->boundingRect().height()) / 2;
    auto ais = GameLogic::getInstance()->aliveAIs();
    double currentX = this->width() / 2 - ais.length() / 2.0* (177 + 70);
    for (auto &p : ais) {
        PlayerInfoContainer *con = new PlayerInfoContainer(p);
        QObject::connect(con, &PlayerInfoContainer::clicked, this, &GameScene::selectReply);
        con->setParent(this);
        this->addItem(con);
        con->setPos(currentX, cy - con->boundingRect().center().y());
        con->show();
        currentX += (177 + 70);
        ai_containers << con;
    }
}

void GameScene::run()
{
    if (is_prepared)
    {
        GameLogic::getInstance()->start();
    }
}

void GameScene::prepareFortargetSelect(bool is_select)
{
    auto cm = qobject_cast<CardItemManager *>(sender());
    if (is_select) {
        current_judge_card = cm->currentSelected();
        if (current_judge_card->cardInfo()->targetFix()) {
            emit selectReply(HumanPlayer::getInstance());
            return;
        }
        for (auto &p : ai_containers)
            p->setTargetSelect(true);
    }
    else {
        current_judge_card = nullptr;
        for (auto &p : ai_containers)
            p->setTargetSelect(false);
    }

}

void GameScene::selectReply(AbstractPlayer *player)
{
    emit HumanPlayer::getInstance()->cardUsed(dash_board->currentSelectCard()->cardInfo(),player);
}

void GameScene::onGameFinished(bool win)
{
    is_prepared = false;
    if (win)
        this->win->show();
    else
        this->lose->show();
}

void GameScene::dealFinishedReply(QString chosen)
{
    if (chosen == "power") {
        HumanPlayer::getInstance()->setPower(HumanPlayer::getInstance()->power() + 1);
    }
    else if (chosen == "agility") {
        HumanPlayer::getInstance()->setAgility(HumanPlayer::getInstance()->agility() + 1);
    }
    else if (chosen == "intelligence") {
        HumanPlayer::getInstance()->setIntelligence(HumanPlayer::getInstance()->intelligence() + 1);
    }
    else if (chosen == "max_hp") {
        HumanPlayer::getInstance()->setMaxHp(HumanPlayer::getInstance()->maxHp() + 10);
    }
    else if(chosen == "Fine!") {
        GameLogic::getInstance()->setGameScene(nullptr);
        BlueMoon::getInstance()->loadScene(new StartScene(nullptr));
        return;
    }
    GameLogic::getInstance()->prepareGameScene(this->getCurrentLevel() + 1);
}

PlayerInfoContainer::PlayerInfoContainer(AbstractPlayer *p /*= nullptr*/)
    :player(p)
{
    avatar = new PlayerAvatarContainer(p);
    avatar->setParent(this);
    avatar->setParentItem(this);
    avatar->setPos(0, 0);

    bar = new HpBar(avatar->boundingRect().width(), p->maxHp(), p->hp());
    bar->setParent(this);
    bar->setParentItem(this);
    bar->setPos(0, avatar->boundingRect().height());

    boundary = new QGraphicsDropShadowEffect(this);
    boundary->setOffset(0);
    boundary->setBlurRadius(50);
    boundary->setColor("white");
    setGraphicsEffect(boundary);
    boundary->setEnabled(true);
   
    setAcceptHoverEvents(false);
    setAcceptedMouseButtons(Qt::NoButton);

    createMarkItem();

    QObject::connect(p, &AbstractPlayer::currentChanged, this, &PlayerInfoContainer::setCurrent);

}

PlayerInfoContainer::~PlayerInfoContainer()
{
    
}

QRectF PlayerInfoContainer::boundingRect() const
{
    return QRectF(0,0,avatar->boundingRect().width(),avatar->boundingRect().height()+bar->boundingRect().height() + 40);
}

void PlayerInfoContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{
    
}

void PlayerInfoContainer::setHp(int hp, int max_hp)
{
    bar->setHp(hp, max_hp);
}

void PlayerInfoContainer::setAlive(bool alive)
{
    avatar->updateAlive(alive);
}

void PlayerInfoContainer::createMarkItem()
{
    for (auto &p : marks_value) {
        if (p)
            p->deleteLater();
    }
    marks_key.clear();
    marks_value.clear();
    int currentX = this->boundingRect().width()-50;
    for (auto &s : player->getMarks()) {
        if (player->markNumber(s) > 0) {
            marks_key.push_back(s);
            MarkItem *mark_item = new MarkItem(s, player->markNumber(s));
            mark_item->setParent(this);
            mark_item->setParentItem(this);
            mark_item->setPos(currentX, this->boundingRect().height() - mark_item->boundingRect().height());
            marks_value.push_back(mark_item);
            currentX -= 40;
        }
    }
}

void PlayerInfoContainer::updateMark(const QString &name)
{
    if (marks_key.contains(name)) {
        // update number;
        if (HumanPlayer::getInstance()->markNumber(name) > 0) {
            marks_value.at(marks_key.indexOf(name))->setNumber(HumanPlayer::getInstance()->markNumber(name));
        }
        else {
            // create new
            createMarkItem();
        }
    }
    else {
        marks_key << name;
        MarkItem *item = new MarkItem(name, HumanPlayer::getInstance()->markNumber(name));
        item->setParent(this);
        this->setParentItem(this);
        this->setPos(this->boundingRect().width() - marks_key.length() * 40 - 10, 0);
        marks_value << item;
    }
}

void PlayerInfoContainer::setCurrent(bool current)
{
    if (current)
        boundary->setColor("purple");
    else
        boundary->setColor("white");
}

void PlayerInfoContainer::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    boundary->setColor("gold");
}

void PlayerInfoContainer::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    boundary->setColor("white");
}

void PlayerInfoContainer::setTargetSelect(bool is_select)
{
    setAcceptHoverEvents(is_select);
    setAcceptedMouseButtons(is_select ? Qt::LeftButton : Qt::NoButton);
    setOpacity(1);
    if (!is_select) return;
    Card *info = qobject_cast<GameScene *>(scene())->dashBoard()->currentSelectCard()->cardInfo();
    if (info->filterTarget(player)) {
        setAcceptHoverEvents(is_select);
        setAcceptedMouseButtons(Qt::LeftButton);
    }
    else {
        setOpacity(0.5);
        setAcceptHoverEvents(false);
        setAcceptedMouseButtons(Qt::NoButton);
    }
    
}

void PlayerInfoContainer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void PlayerInfoContainer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit this->clicked(player);
}

GameFinishPrompt::GameFinishPrompt(bool win)
    :QGraphicsObject(nullptr),is_win(win)
{
    next_level = 0;
    prompt = new QGraphicsSimpleTextItem(this);
    prompt->setFont(UIUtility::getInfoBarnerFont());
    if (is_win) {
        prompt->setText(QString("The Next Level is %1, Please Choose Reward:").arg(QString::number(next_level)));
    }
    else {
        prompt->setText(QString("You Have Been DEFEAT, Good Luck!"));
    }
    prompt->setParentItem(this);
    prompt->setPos((this->boundingRect().width() - prompt->boundingRect().width()) / 2, 15);
    int currentY = prompt->boundingRect().height() + 15;
    if (is_win) {
        // create reward
        int currentX = 20;
        AvatarButton *p = new AvatarButton("power", "power");
        p->setParent(this);
        p->setParentItem(this);
        p->setPos(currentX, currentY + 50);
        QObject::connect(p, &AvatarButton::click, this,&GameFinishPrompt::dealOptionChosen);
        options["power"] = p;
        currentX += 200;

        p = new AvatarButton("agility", "agility");
        p->setParent(this);
        p->setParentItem(this);
        p->setPos(currentX, currentY + 50);
        QObject::connect(p, &AvatarButton::click, this, &GameFinishPrompt::dealOptionChosen);
        options["agility"] = p;
        currentX += 200;

        p = new AvatarButton("intelligence", "intelligence");
        p->setParent(this);
        p->setParentItem(this);
        p->setPos(currentX, currentY + 50);
        QObject::connect(p, &AvatarButton::click, this, &GameFinishPrompt::dealOptionChosen);
        options["intelligence"] =  p;
        currentX += 200;

        p = new AvatarButton("max_hp", "max_hp");
        p->setParent(this);
        p->setParentItem(this);
        p->setPos(currentX, currentY + 50);
        QObject::connect(p, &AvatarButton::click, this, &GameFinishPrompt::dealOptionChosen);
        options["max_hp"] =  p;
        currentX += 200;

        currentY += 250;
    }
    else {
        currentY += 30;
    }
    ok = new Button("OK");
    ok->setParent(this);
    ok->setParentItem(this);
    ok->setPos(this->boundingRect().width() / 2 - ok->boundingRect().width() / 2, currentY);
    ok->setEnabled(!is_win);

    connect(ok, &Button::click, [this]() {
        if (this->is_win && !current_option.isEmpty())
            this->reply(current_option);
        else
            this->reply("Fine!");
    });
}

GameFinishPrompt::~GameFinishPrompt()
{
    delete prompt;
}

void GameFinishPrompt::setInfo(int next_level)
{
    this->next_level = next_level;
    prompt->setPos((this->boundingRect().width() - prompt->boundingRect().width()) / 2, 15);
}

QRectF GameFinishPrompt::boundingRect() const
{
    int width = 0, h = 0;
    if (is_win) {
        width = qMax<int>(
            prompt->boundingRect().width()
            ,
            5 * 150
        );
        width += 40;
        h = prompt->boundingRect().height() + 200 + 50 * 3 + 60 + ok->boundingRect().height();
    }   
    else {
        width = prompt->boundingRect().width() + 40;
        h = ok->boundingRect().height() + prompt->boundingRect().height() + 60;
    }
    return QRectF(0, 0, width, h);

}

void GameFinishPrompt::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
}

void GameFinishPrompt::dealOptionChosen(QString chosen)
{
    if (chosen != this->current_option) {
        if (!this->current_option.isEmpty())
            options[this->current_option]->setSelected(false);
        this->options[chosen]->setSelected(true);
        this->current_option = chosen;
        ok->setEnabled(true);
    }
    else {
        if (!this->current_option.isEmpty())
            options[this->current_option]->setSelected(false);
        this->current_option = "";
        ok->setEnabled(false);
    }
}
