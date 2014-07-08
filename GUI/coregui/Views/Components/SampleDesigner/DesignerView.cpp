#include "DesignerView.h"
#include "DesignerMimeData.h"
#include "DesignerScene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QShortcut>
#include <QDebug>

#include "LayerView.h"
#include "LayerView.h"

#include "styledbar.h"

#include <cmath>
#include <iostream>


DesignerView::DesignerView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    setAcceptDrops(true);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
//   QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
//   connect(shortcut, SIGNAL(activated()), this, SLOT(deleteItem()));

    setDragMode(QGraphicsView::RubberBandDrag);

}


//void SampleEditorView::wheelEvent(QWheelEvent *event)
//{
//    scaleView(std::pow((double)2, -event->delta() / 240.0));
//}


void DesignerView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    //m_graphicsView->scale(scaleFactor, scaleFactor);
    scale(scaleFactor, scaleFactor);
}


void DesignerView::zoomIn()
{
    scaleView(1.1);
}


void DesignerView::zoomOut()
{
    scaleView(0.9);
}

//! zoom view to show all items
void DesignerView::zoomFit()
{
//    m_graphicsView->fitInView(m_graphicsView->scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
    fitInView(scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
}


void DesignerView::clearAll()
{
    //m_graphicsView->scene()->clear();
    scene()->clear();
}


void DesignerView::deleteSelectedItems()
{
    DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
    Q_ASSERT(designerScene);
    designerScene->deleteSelectedItems();
}


void DesignerView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Space:
        if(dragMode() != QGraphicsView::ScrollHandDrag && !event->isAutoRepeat()) {
            setDragMode(QGraphicsView::ScrollHandDrag);
            setInteractive(false);
            qDebug() << "  space pressed" << event->isAutoRepeat();
        }
        break;
    case Qt::Key_Delete:
        deleteSelectedItems();
        break;
    case Qt::Key_Backspace:
        deleteSelectedItems();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void DesignerView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:

        if(dragMode() == QGraphicsView::ScrollHandDrag && !event->isAutoRepeat()) {
            setDragMode(QGraphicsView::RubberBandDrag);
            setInteractive(true);
            qDebug() << "  space released" << event->isAutoRepeat();
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }

}


void DesignerView::mouseMoveEvent(QMouseEvent * event)
{
    QGraphicsView::mouseMoveEvent(event);
}


