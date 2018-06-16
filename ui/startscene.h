#pragma once

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QGraphicsTextItem>

class Button;
class AvatarButton;

class Logo final : public QGraphicsObject
{
     Q_OBJECT
public:
    Logo();

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

private:

};

class ChooseGeneralPanel final : public QGraphicsObject
{
    Q_OBJECT
public:
    ChooseGeneralPanel(QGraphicsItem *parent = nullptr);
    ~ChooseGeneralPanel();

    void parse(const QStringList &generals);

    virtual QRectF boundingRect()const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;
signals:
    void backClicked();
    void generalChosen(QString);
    void startClicked(QString);
private slots:
    void onDealChosen(QString chosen);
private:
    QHash<QString, AvatarButton *> buttons;
    QGraphicsTextItem *title;
    Button *back, *start;
    QString selected;
};

class StartScene final : public QGraphicsScene
{
    Q_OBJECT

public:
    StartScene(QObject *parent);
    ~StartScene();
public slots:
    void onGeneralConfirmed(const QString &general);
protected:
    void createMenu();
    void createCooseGeneralPannel();
private:
    Logo * logo;
    QList<Button *> buttons;

    ChooseGeneralPanel *choose_general;
};
