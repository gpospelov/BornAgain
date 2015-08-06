#include "MaskGraphicsView.h"
#include "GraphicsProxyWidget.h"
#include "MaskGraphicsScene.h"


//GraphicsView::GraphicsView() : m_rectangle(0), m_ellipse(0), m_polygon(0), isFinished(true),
//    m_currentMousePosition(QPointF(0,0)), m_lastAddedPoint(QPointF(0,0))
//{
//    m_drawing = NONE;
//}


void MaskGraphicsView::wheelEvent(QWheelEvent *event)
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


void MaskGraphicsView::keyPressEvent(QKeyEvent *event )
{
    switch ( event->key() ) {
        case Qt::Key_Delete:
            deleteSelectedItems();
            break;
        case Qt::Key_Space:
            if(!event->isAutoRepeat())
                emit panMode(true);
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
    }
}
void MaskGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
        case Qt::Key_Space:
        if(!event->isAutoRepeat())
            emit panMode(false);
        break;
        default:
        QWidget::keyReleaseEvent(event);
        break;
    }
}


void MaskGraphicsView::deleteSelectedItems()
{
    MaskGraphicsScene *graphicsScene = dynamic_cast<MaskGraphicsScene *>(scene());
    Q_ASSERT(graphicsScene);
    graphicsScene->deleteSelectedItems();
}

bool MaskGraphicsView::controlButtonIsPressed(QWheelEvent *event)
{
    if(event->modifiers().testFlag(Qt::ControlModifier)){
        return true;
    }
    else {
        return false;
    }
}

bool MaskGraphicsView::eventPosIsOnColorMap(QWheelEvent *event)
{
    if(this->scene()->items()[0]->boundingRect().contains(event->pos())) {
        return true;
    }
    else {
        return false;
    }
}
