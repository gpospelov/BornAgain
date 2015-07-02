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
            this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
    else if(eventPosIsOnColorMap(event)) {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QGraphicsView::wheelEvent(event);
    }
    else {
        QGraphicsView::wheelEvent(event);
    }
}

void MaskGraphicsView::resizeEvent(QResizeEvent *event)
{
//    qDebug() << "resize";
//    for(int i = 0; i < scene()->items().length()-1; ++i)
//    {
//        if(this->scene()->items()[i]->type() == QGraphicsProxyWidget::Type) {
//            dynamic_cast<GraphicsProxyWidget*>(this->scene()->items()[i])->resize(this->viewport()->width(), this->viewport()->height());
//            this->setSceneRect(this->rect());
//        }
//    }


//    this->scale(this->rect().width()/this->scene()->width(), this->rect().height()/this->scene()->height());
/*    qreal width = this->sceneRect().width() * this->rect().width()/this->scene()->width();
    qreal height =  this->sceneRect().height() * this->rect().height()/this->scene()->height();
    this->scene()->sceneRect().setWidth(width);
    this->scene()->sceneRect().setHeight(height)*/;
    QGraphicsView::resizeEvent(event);
}

void  MaskGraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete:
        deleteSelectedItems();
        break;
    default:
        QWidget::keyPressEvent(event);
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
