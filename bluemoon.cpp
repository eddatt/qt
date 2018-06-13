#include "bluemoon.h"
#include "ui/startscene.h"

#include <QResizeEvent>

BlueMoon::BlueMoon(QWidget *parent)
    :QMainWindow(parent)
{
    view = new CoreGraphicsView(this);
    setCentralWidget(view);
    resize(QSize(1280, 768));
    setWindowTitle("Qt Blue Moon");
    StartScene *start = new StartScene(this);
    loadScene(start);
}

BlueMoon::~BlueMoon()
{
    if (view) {
        view->deleteLater();
    }
}

void BlueMoon::loadScene(QGraphicsScene *scene)
{
    auto old_scene = view->scene();
    if (old_scene) {
        scene->deleteLater();
    }
    this->view->setScene(scene);
    QResizeEvent e(QSize(view->size().width(), view->size().height()), view->size());
    view->resizeEvent(&e);
}

void BlueMoon::fitBackgroundBrush()
{
    auto scene = view->scene();
    if (scene) {
        QBrush brush(scene->backgroundBrush());
        QPixmap pixmap(brush.texture());

        QRectF rect(scene->sceneRect());
        QTransform transform;
        transform.translate(-rect.left(), -rect.top());
        transform.scale(rect.width() / pixmap.width(), rect.height() / pixmap.height());
        brush.setTransform(transform);
        scene->setBackgroundBrush(brush);
    }
}

CoreGraphicsView::CoreGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{
    setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setSceneRect(QRectF(0, 0, 1280, 720));
}

void CoreGraphicsView::resizeEvent(QResizeEvent *event)   // do transform
{
    QGraphicsView::resizeEvent(event);
    if (scene()) {
        QGraphicsScene *scene = this->scene();
        QRectF newSceneRect(0, 0, event->size().width(), event->size().height());
        scene->setSceneRect(newSceneRect);
        if (scene->sceneRect().size() != event->size()) {
            QSizeF from(scene->sceneRect().size());
            QSizeF to(event->size());
            QTransform transform;
            transform.scale(to.width() / from.width(), to.height() / from.height());
            setTransform(transform);
        }
        else {
            resetTransform();
        }
        setSceneRect(scene->sceneRect());
    }
    BlueMoon *parent = qobject_cast<BlueMoon *>(parentWidget());
    if (parent) {
        parent->fitBackgroundBrush();
    }
}
