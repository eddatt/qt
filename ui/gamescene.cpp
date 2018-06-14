#include "gamescene.h"
#include "logic/player.h"
#include "uiutility.h"
#include "infobarner.h"

#include <QPixmap>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    :QGraphicsScene(parent)
{
    this->setBackgroundBrush(QPixmap("res/bg.jpg"));
    setSceneRect(QRectF(0, 0, 1280, 700));
    dash_board = DashBoard::getInstance();
    barner = InfoBanner::getInstance();
}

GameScene *GameScene::getInstance()
{
    static GameScene scene(nullptr);
    return &scene;
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




DashBoard * DashBoard::getInstance()
{
    static DashBoard dash;
    return &dash;
}

QRectF DashBoard::boundingRect() const
{
    double width = GameScene::getInstance()->width();
    return QRectF(0, 0, width, 300);
}

void DashBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */)
{

}

DashBoard::~DashBoard()
{

}

DashBoard::DashBoard()
{

}
