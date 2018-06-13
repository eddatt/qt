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
    Logo(const QString &filename);

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

private:
    QPixmap pixmap;

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
private:
    QHash<QString, AvatarButton *> buttons;
    QGraphicsTextItem *title;
    Button *back;
};

class StartScene final : public QGraphicsScene
{
    Q_OBJECT

public:
    StartScene(QObject *parent);
    ~StartScene();
protected:
    void createMenu();
    void createCooseGeneralPannel();
private:
    Logo * logo;
    QList<Button *> buttons;

    QGraphicsItemGroup *choose_general;
};
