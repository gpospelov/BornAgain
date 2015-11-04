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
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QTransform>
#include <QDebug>

MaskGraphicsView::MaskGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , m_colorMapProxy(0)
{
    setObjectName(QStringLiteral("MaskGraphicsView"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
    setMouseTracking(true);
}

void MaskGraphicsView::setColorMapProxy(MaskGraphicsProxy *colorMapProxy)
{
    m_colorMapProxy = colorMapProxy;
}

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

void MaskGraphicsView::resizeEvent(QResizeEvent *event)
{
    qDebug() << "   MaskGraphicsView::resizeEvent()" << event->size();
    qDebug() << "       sceneRect" << scene()->sceneRect();
    qDebug() << "       transform" << transform();
    QWidget::resizeEvent(event);

//    QTransform trans = transform();
    fitInView(QRectF(0, 0, 800, 600), Qt::KeepAspectRatio);


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
    qDebug() << "MaskGraphicsView::mouseMoveEvent ->"
             << event->pos() << "scene_coord:" << mapToScene(event->pos());
    qDebug() << "  transform():" <<transform();
//    QPoint p = mapFromScene(800, 600);
//    qDebug() << "   mapFromScene(800, 600):" << p << " mapToScene(p)" << mapToScene(p);

    QGraphicsView::mouseMoveEvent(event);
}

bool MaskGraphicsView::controlButtonIsPressed(QWheelEvent *event)
{
    if(event->modifiers().testFlag(Qt::ControlModifier)){
        return true;
    }
    return false;
}

