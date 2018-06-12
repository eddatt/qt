#pragma once

#include <QObject>

class GameLogic : public QObject
{
    Q_OBJECT

public:
    GameLogic(QObject *parent);
    ~GameLogic();
};
