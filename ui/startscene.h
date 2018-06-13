#pragma once

#include <QGraphicsScene>
#include <QGraphicsObject>

class Button;

class Logo : public QGraphicsObject {
     Q_OBJECT
public:
    Logo(const QString &filename);

    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = Q_NULLPTR */) override;

private:
    QPixmap pixmap;

};

class StartScene : public QGraphicsScene
{
    Q_OBJECT

public:
    StartScene(QObject *parent);
    ~StartScene();
protected:
    void createMenu();
private:
    Logo * logo;

    QList<Button *> buttons;
};
