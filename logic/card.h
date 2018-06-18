#pragma once
#include <QString>
class CardItem;
class AbstractPlayer;

class Card
{
public:
    Card(const QString &name);
    virtual ~Card();

    virtual bool isAvailable() const;

    CardItem *cardItem() const;
    QString name() const;

    virtual bool targetFix() const;
    virtual bool filterTarget(AbstractPlayer *target) const;
    virtual void doEffect(AbstractPlayer *target);

	static Card* generateCard();

	int energy() const;
	void setEnergy(int e);

protected:
    QString m_name;
    CardItem *item;
	int m_energy;

};

class Kill :public Card {
public:
	Kill();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Jink :public Card {
public:
	Jink();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Wine :public Card {
public:
	Wine();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Peach :public Card {
public:
	Peach();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Guisuo:public Card {
public:
	Guisuo();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Maifu :public Card {
public:
	Maifu();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Songjian :public Card {
public:
	Songjian();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Shengnu :public Card {
public:
	Shengnu();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Xianji :public Card {
public:
	Xianji();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

class Zhongji :public Card {
public:
	Zhongji();
	virtual bool targetFix() const;
	virtual bool filterTarget(AbstractPlayer *target) const;
	virtual void doEffect(AbstractPlayer *target);
};

