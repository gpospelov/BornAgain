#include "ObsoleteMaskGraphicsView.h"
#include "ObsoleteGraphicsProxyWidget.h"
#include "ObsoleteMaskGraphicsScene.h"


ObsoleteMaskGraphicsView::ObsoleteMaskGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
}


void ObsoleteMaskGraphicsView::wheelEvent(QWheelEvent *event)
{
    // hold control button
    if(controlButtonIsPressed(event)) {
        centerOn(mapToScene(event->pos()));

        // Scale the view / do the zoom
        const double scaleFactor = 1.15;

        if(event->delta() > 0) {
            // Zoom in
            this->scale(scaleFactor, scaleFactor);

        } else {
            // Zooming out
            if(horizontalScrollBar()->isVisible() || verticalScrollBar()->isVisible())
                this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
//    else if(eventPosIsOnColorMap(event)) {
//        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        QGraphicsView::wheelEvent(event);
//    }
    else {
        QGraphicsView::wheelEvent(event);
    }
}
void ObsoleteMaskGraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete:
        emit deleteSelectedItems();
        break;
    case Qt::Key_Space:
        if (!event->isAutoRepeat())
            panMode(true);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}
void ObsoleteMaskGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        if (!event->isAutoRepeat())
            panMode(false);
        break;
    default:
        QWidget::keyReleaseEvent(event);
        break;
    }
}


bool ObsoleteMaskGraphicsView::controlButtonIsPressed(QWheelEvent *event)
{
    if(event->modifiers().testFlag(Qt::ControlModifier)){
        return true;
    }
    return false;
}

bool ObsoleteMaskGraphicsView::eventPosIsOnColorMap(QWheelEvent *event)
{
    if(this->scene()->items()[0]->boundingRect().contains(event->pos())) {
        return true;
    }
    return false;
}
