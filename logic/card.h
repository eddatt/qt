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

    CardItem *cardItem() const;
    QString name() const;

    virtual void doEffect(AbstractPlayer *self, AbstractPlayer *target);

protected:
    QString m_name;
    CardItem *item;

};

