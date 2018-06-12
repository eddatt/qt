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
    BlueMoon(QWidget *parent = nullptr);
    ~BlueMoon();
    
    void loadScene(QGraphicsScene *scene);
public slots:
    void fitBackgroundBrush();
private:
    CoreGraphicsView * view;
};
