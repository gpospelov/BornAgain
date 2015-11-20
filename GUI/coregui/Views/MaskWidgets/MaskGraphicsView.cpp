// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsView.cpp
//! @brief     Implements class MaskGraphicsView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskGraphicsView.h"
#include "MaskGraphicsProxy.h"
#include "MaskGraphicsScene.h"
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QTransform>
#include <QDebug>

namespace {
const double min_zoom_value = 1.0;
const double max_zoom_value = 5.0;
const double zoom_step = 0.05;
}

MaskGraphicsView::MaskGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
//    , m_colorMapProxy(0)
    , m_current_zoom_value(1.0)
{
    setObjectName(QStringLiteral("MaskGraphicsView"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
    setMouseTracking(true);
}

//! Reset given view to original zoom state. Also assks graphics scene to do the same with color map.
void MaskGraphicsView::onResetViewRequest()
{
    qDebug() << "MaskGraphicsView::onResetViewRequest()";
    setZoomValue(1.0);
    MaskGraphicsScene *maskScene = dynamic_cast<MaskGraphicsScene *>(scene());
    maskScene->onResetViewRequest();
}

//void MaskGraphicsView::setColorMapProxy(MaskGraphicsProxy *colorMapProxy)
//{
//    m_colorMapProxy = colorMapProxy;
//}

//void MaskGraphicsView::wheelEvent(QWheelEvent *event)
//{
//    // hold control button
//    if(isControlButtonIsPressed(event)) {
//        centerOn(mapToScene(event->pos()));

//        // Scale the view / do the zoom
//        const double scaleFactor = 1.15;

//        if(event->delta() > 0) {
//            // Zoom in
//            this->scale(scaleFactor, scaleFactor);

//        } else {
//            // Zooming out
//            if(horizontalScrollBar()->isVisible() || verticalScrollBar()->isVisible())
//                this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
//        }
//    }
////    else if(eventPosIsOnColorMap(event)) {
////        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
////        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
////        QGraphicsView::wheelEvent(event);
////    }
//    else {
//        QGraphicsView::wheelEvent(event);
//    }


//}


void MaskGraphicsView::wheelEvent(QWheelEvent *event)
{
    // hold control button
    if(isControlButtonIsPressed(event)) {
        centerOn(mapToScene(event->pos()));

        if(event->delta() > 0) {
            // Zoom in
            increazeZoomValue();

        } else {
            // Zooming out
            if(horizontalScrollBar()->isVisible() || verticalScrollBar()->isVisible())
                decreazeZoomValue();
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



void MaskGraphicsView::resizeEvent(QResizeEvent *event)
{
    qDebug() << "   MaskGraphicsView::resizeEvent()" << event->size();
    qDebug() << "       sceneRect" << scene()->sceneRect();
    qDebug() << "       transform" << transform();
    QWidget::resizeEvent(event);

    foreach (QGraphicsItem *graphicsItem, scene()->items()) {
        if(MaskGraphicsProxy *proxy = dynamic_cast<MaskGraphicsProxy *>(graphicsItem)) {
            proxy->resize(event->size());
            scene()->setSceneRect(0,0,event->size().width(),event->size().height());
            proxy->setPos(0,0);
            qDebug() << "!!! Resizing" << this->size() << event->size();
        }
    }




//    QTransform trans = transform();
//    fitInView(QRectF(0, 0, 800, 600), Qt::KeepAspectRatio);


////    QGraphicsRectItem *b_rec = dynamic_cast<QGraphicsRectItem *>(scene()->items().back());
////    Q_ASSERT(b_rec);
//    QRectF oldRect = QRectF(0,0,800, 600);
//    QPoint p = mapFromScene(800, 600);
////    QRectF newRect = QRectF(0,0,p.x(), p.y());
//    QRectF newRect = trans.mapRect(oldRect);
////    b_rec->setRect(newRect);
////    b_rec->update(newRect);
//////    b_rec->setRect(QRectF(oldRect.x(), oldRect.y(), oldRect.width()*trans.m11(), oldRect.height()*trans.m22() ));
//    qDebug() << "p:" << p << "       oldRect:" << oldRect << "  newRect:" << newRect;
////    qDebug() << "trans.m11()" << oldRect.width()*trans.m11() << oldRect.height()*trans.m22();

////    qDebug() << "   mapFromScene:" << p << " toScene:" << mapToScene(p);


//    //    m_colorMapProxy->resize(event->size());
//    //    m_colorMapProxy->widget()->resize(event->size());
//    m_colorMapProxy->setPos(newRect.x(), newRect.y());
//    m_colorMapProxy->resize(newRect.width(), newRect.height());
//    m_colorMapProxy->widget()->resize(newRect.width(), newRect.height());

}

void MaskGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << "MaskGraphicsView::mouseMoveEvent ->"
//             << event->pos() << "scene_coord:" << mapToScene(event->pos())
//             << " view_size:" << size() << " viewport:" << viewport()->size();

//    qDebug() << "  transform():" <<transform();

    QGraphicsView::mouseMoveEvent(event);
}

void MaskGraphicsView::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MaskGraphicsView::keyPressEvent";
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Space:
        if(!event->isAutoRepeat()) {
            emit changeActivityRequest(MaskEditorFlags::PAN_ZOOM_MODE);
        }
        break;
    case Qt::Key_Escape:
        cancelCurrentDrawing();
        break;
    case Qt::Key_PageUp:
        bringToFront();
        break;
    case Qt::Key_PageDown:
        sendToBack();
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

void MaskGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        if(!event->isAutoRepeat()) {
            emit changeActivityRequest(MaskEditorFlags::SELECTION_MODE);
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }

}


bool MaskGraphicsView::isControlButtonIsPressed(QWheelEvent *event)
{
    if(event->modifiers().testFlag(Qt::ControlModifier)){
        return true;
    }
    return false;
}

void MaskGraphicsView::deleteSelectedItems()
{
    MaskGraphicsScene *maskScene = dynamic_cast<MaskGraphicsScene *>(scene());
    Q_ASSERT(maskScene);
    maskScene->deleteSelectedItems();
}

void MaskGraphicsView::cancelCurrentDrawing()
{
    MaskGraphicsScene *maskScene = dynamic_cast<MaskGraphicsScene *>(scene());
    Q_ASSERT(maskScene);
    maskScene->cancelCurrentDrawing();
}

void MaskGraphicsView::bringToFront()
{
    MaskGraphicsScene *maskScene = dynamic_cast<MaskGraphicsScene *>(scene());
    maskScene->onMaskStackingOrderChanged(MaskEditorFlags::BRING_TO_FRONT);
}

void MaskGraphicsView::sendToBack()
{
    MaskGraphicsScene *maskScene = dynamic_cast<MaskGraphicsScene *>(scene());
    maskScene->onMaskStackingOrderChanged(MaskEditorFlags::SEND_TO_BACK);
}

void MaskGraphicsView::setZoomValue(double zoom_value)
{
    if(zoom_value == m_current_zoom_value) return;

    QMatrix oldMatrix = matrix();
    resetMatrix();
    translate(oldMatrix.dx(), oldMatrix.dy());
    scale(zoom_value, zoom_value);
    m_current_zoom_value = zoom_value;
}

void MaskGraphicsView::decreazeZoomValue()
{
    double zoom_value = m_current_zoom_value - zoom_step;
    if(zoom_value < min_zoom_value) zoom_value = min_zoom_value;
    setZoomValue(zoom_value);
}

void MaskGraphicsView::increazeZoomValue()
{
    double zoom_value = m_current_zoom_value + zoom_step;
    if(zoom_value > max_zoom_value) zoom_value = max_zoom_value;
    setZoomValue(zoom_value);
}


