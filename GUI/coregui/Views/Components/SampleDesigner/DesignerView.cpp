#include "DesignerView.h"
#include "DesignerMimeData.h"
#include "DesignerScene.h"
#include "GUIHelpers.h"
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

int DesignerView::getSelectionMode() const
{
    if (dragMode() == QGraphicsView::NoDrag) {
        return SimpleSelectionMode;
    }
    else if(dragMode() == QGraphicsView::RubberBandDrag) {
        return RubberSelectionMode;
    }
    else if(dragMode() == QGraphicsView::ScrollHandDrag) {
        return HandDragMode;
    }
    else {
        throw GUIHelpers::Error("DesignerView::getSelectionMode() -> Error.");
    }
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


void DesignerView::onSceneScaleChanged(const QString &scale_string)
{
    qDebug() << "onSceneScaleChanged";
    double newScale = scale_string.left(scale_string.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = matrix();
    resetMatrix();
    translate(oldMatrix.dx(), oldMatrix.dy());
    scale(newScale, newScale);

}


void DesignerView::onSelectionMode(int mode)
{
    switch(mode) {
    case SimpleSelectionMode:
        setDragMode(QGraphicsView::NoDrag);
        setInteractive(true);
        emit selectionModeChanged(SimpleSelectionMode);
        break;
    case RubberSelectionMode:
        setDragMode(QGraphicsView::RubberBandDrag);
        setInteractive(true);
        emit selectionModeChanged(RubberSelectionMode);
        break;
    case HandDragMode:
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
        emit selectionModeChanged(HandDragMode);
        break;
     default:
        break;
    }
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
        if( getSelectionMode() != HandDragMode && !event->isAutoRepeat()) {
            onSelectionMode(HandDragMode);
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

        if( getSelectionMode() != RubberSelectionMode && !event->isAutoRepeat()) {
            onSelectionMode(RubberSelectionMode);
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


