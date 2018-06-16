#include "gamescene.h"
#include "logic/player.h"
#include "uiutility.h"
#include "infobarner.h"
#include "dash_board.h"

#include <QPixmap>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    :QGraphicsScene(parent)
{
    setSceneRect(UIUtility::getGraphicsSceneRect());
    dash_board = new DashBoard;
    dash_board->setParent(this);
    this->addItem(dash_board);
    dash_board->setPos(0, UIUtility::getGraphicsSceneRect().height() - dash_board->boundingRect().height());
    dash_board->show();

    barner = new InfoBanner;
    barner->setParent(this);
    this->addItem(barner);
    barner->setPos(0, 0);
    barner->show();
    this->setBackgroundBrush(QPixmap(UIUtility::getBackgroundPath("on_game")));
}


/*
__________________________________________________________________________
General Name   Hp             Property                           Cards            
__________________________________________________________________________
Items
__________________________________________________________________________
                               _____________
                              |             |
                              |             |
                              |             |
                              |             |
                              |             |
                              |             |
                              |_____________|
                              |             |
                              |_____________|



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

