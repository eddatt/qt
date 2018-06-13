#pragma once

#include <QMainWindow>
#include <QGraphicsView>

class CoreGraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    CoreGraphicsView(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event);
};

class BlueMoon : public QMainWindow
{
    Q_OBJECT
public:
    static BlueMoon *getInstance();
    ~BlueMoon();
    
    void loadScene(QGraphicsScene *scene);
public slots:
    void fitBackgroundBrush();
private:
    CoreGraphicsView * view;

    BlueMoon(QWidget *parent = nullptr);
};
