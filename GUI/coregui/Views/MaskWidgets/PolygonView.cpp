// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/PolygonView.cpp
//! @brief     Implements PolygonView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PolygonView.h"
#include "MaskEditorHelper.h"
#include "MaskItems.h"
#include "PolygonPointView.h"
#include <QPainter>
#include <QCursor>
#include <QRectF>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace {
const double bbox_margins = 5; // additional margins around points to form bounding box
}

PolygonView::PolygonView()
    : m_block_on_point_update(false)
    , m_closed_polygon(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
//    setAcceptHoverEvents(true);
}

void PolygonView::addView(IMaskView *childView, int row)
{
    qDebug() << "PolygonView::addView, calling update_polygon" << m_block_on_point_update;
    Q_UNUSED(row);

    PolygonPointView *pointView = qgraphicsitem_cast<PolygonPointView *>(childView);
    Q_ASSERT(pointView);

    // first polygon point will change it's color when mouse is on hover
    if(childItems().isEmpty()) pointView->setAcceptHoverEvents(true);
    pointView->setParentItem(this);


//    connect(childView, SIGNAL(xChanged()), this, SLOT(update_view()));
//    connect(childView, SIGNAL(yChanged()), this, SLOT(update_view()));
//    childView->setVisible(false);
    pointView->setVisible(true);

    update_polygon();

    connect(pointView, SIGNAL(propertyChanged()), this, SLOT(update_view()));
    connect(pointView, SIGNAL(closePolygonRequest()), this, SLOT(onClosePolygonRequest()));

}

//void PolygonView::onPropertyChange(const QString &propertyName)
//{
////    qDebug() <<
//    update_polygon();
//}

void PolygonView::onChangedX()
{
//    qDebug() << "PolygonView::onChangedX()";
//    update_points();
}

void PolygonView::onChangedY()
{
//    qDebug() << "PolygonView::onChangedY()";
    //    update_points();
}

void PolygonView::onClosePolygonRequest()
{
    qDebug() << "PolygonView::onClosePolygonRequest()";
    foreach(QGraphicsItem *childItem, childItems()) {
        childItem->setAcceptHoverEvents(false);
        childItem->setCursor(Qt::SizeAllCursor);
    }
    m_closed_polygon = true;
}

//void PolygonView::onChilderChanged()
//{
//    qDebug() << "PolygonView::onChilderChanged()";
////    update_polygon();

//}

void PolygonView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_ASSERT(m_item);
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();
    bool mask_value = m_item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));

    painter->drawPolyline(m_polygon.toPolygon());

    if(m_closed_polygon) {
        painter->drawPolygon(m_polygon.toPolygon());
    }

}

QVariant PolygonView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug() << "PolygonView::itemChange" << change;
    if(change == QGraphicsItem::ItemSelectedHasChanged) {
//        if(this->isSelected()) {
//            setChildrenVisible(this->isSelected());
//        } else {
//            setChildrenVisible(false);
//        }
    }
    return QGraphicsItem::itemChange(change, value);

}

void PolygonView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "PolygonView::mouseMoveEvent" << event->scenePos();

    IMaskView::mouseMoveEvent(event);
    update_points();

//    foreach(QGraphicsItem *childItem, childItems()) {
//        qDebug() << "updating";
//        QPointF pos = childItem->scenePos();
//        PolygonPointView *view = qgraphicsitem_cast<PolygonPointView *>(childItem);
//        Q_ASSERT(view);
//        view->updateParameterizedItem(pos);

//    }
//    setPos(0,0);
//    update_view();

}

//void PolygonView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    qDebug() << "PolygonView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)";
//}

//void PolygonView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
//{
//    qDebug() << "PolygonView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)";
//}


void PolygonView::update_view()
{
    qDebug() << "PolygonView::update_view()";
    update_polygon();
//    update();
}

void PolygonView::update_polygon()
{
    qDebug() << "PolygonView::update_polygon() 1.1" << m_block_on_point_update;
    if(m_block_on_point_update) return;

    qDebug() << "PolygonView::update_polygon() 1.2";

    m_block_on_point_update = true;

    if (m_item->childItemCount()) {

        m_polygon.clear();

        foreach (ParameterizedItem *item, m_item->childItems()) {
            qreal px = toSceneX(item->getRegisteredProperty(PolygonPointItem::P_POSX).toReal());
            qreal py = toSceneY(item->getRegisteredProperty(PolygonPointItem::P_POSY).toReal());
            m_polygon << QPointF(px, py);
        }

        QRectF scene_rect = m_polygon.boundingRect().marginsAdded(
            QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));

        m_bounding_rect = QRectF(0.0, 0.0, scene_rect.width(), scene_rect.height());

        m_polygon = mapFromScene(m_polygon);

        for (int i = 0; i < childItems().size(); ++i) {
            qDebug() << "!!!" << i;
            QGraphicsItem *childView = childItems()[i];
//            disconnect(childView->toGraphicsObject(), SIGNAL(xChanged()), this,
//                       SLOT(update_view()));
//            disconnect(childView->toGraphicsObject(), SIGNAL(yChanged()), this,
//                       SLOT(update_view()));

            childView->setPos(m_polygon[i]);
//            connect(childView->toGraphicsObject(), SIGNAL(xChanged()), this, SLOT(update_view()));
//            connect(childView->toGraphicsObject(), SIGNAL(yChanged()), this, SLOT(update_view()));
        }

        setPos(scene_rect.x(), scene_rect.y());
    }

    m_block_on_point_update = false;

    qDebug() << "!!!!!";
    qDebug() << "!!!!!";
    qDebug() << "!!!!!";
    qDebug() << "!!!!!";
    qDebug() << "PolygonView::update_polygon() 1.3 !!!!!";

}

void PolygonView::update_points()
{
    qDebug() << "PolygonView::update_points()";
//    return;

    if(m_block_on_point_update) return;

//    m_block_on_point_update = true;
    foreach(QGraphicsItem *childItem, childItems()) {
        PolygonPointView *view = qgraphicsitem_cast<PolygonPointView *>(childItem);
        ParameterizedItem *item = view->getParameterizedItem();
        QPointF pos = view->scenePos();
        qDebug() << "    AAA" << pos;

//        disconnect(view, SIGNAL(xChanged()), this, SLOT(update_view()));
//        disconnect(view, SIGNAL(yChanged()), this, SLOT(update_view()));
        disconnect(view, SIGNAL(propertyChanged()), this, SLOT(update_view()));

        view->updateParameterizedItem(pos);
        connect(view, SIGNAL(propertyChanged()), this, SLOT(update_view()));
//        connect(view, SIGNAL(xChanged()), this, SLOT(update_view()));
//        connect(view, SIGNAL(yChanged()), this, SLOT(update_view()));

//        QPointF pscene(toSceneX(item->getRegisteredProperty(PolygonPointItem::P_POSX).toReal()),
//                       toSceneY(item->getRegisteredProperty(PolygonPointItem::P_POSY).toReal()));
    //        view->setPos(mapFromScene(pscene));

   }

//    m_block_on_point_update = false;
}

void PolygonView::setChildrenVisible(bool value)
{
    foreach(QGraphicsItem *childItem, childItems()) {
        childItem->setVisible(value);
    }
}

//void PolygonView::update_bounding_rect()
//{
//    m_bounding_rect = m_polygon.boundingRect().marginsAdded(QMarginsF(bbox_margins, bbox_margins,
//                                                  bbox_margins, bbox_margins));
//}

