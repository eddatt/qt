#pragma once
#include <QString>
class CardItem;
class AbstractPlayer;

class Card
{
public:
    Card(const QString &name);
    virtual ~Card();

    virtual bool isAvailable(AbstractPlayer *player) const;

    CardItem *generateItem() const;

    virtual void doEffect(AbstractPlayer *self, AbstractPlayer *target);

protected:
    QString name;

};

