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
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace {
const double bbox_margins = 5; // additional margins around points to form bounding box
}

PolygonView::PolygonView()
    : m_block_on_point_update(false)
    , m_closed_polygon(false)
    , m_close_polygon_request(false)
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

    if(childItems().contains(childView)) return;

    PolygonPointView *pointView = dynamic_cast<PolygonPointView *>(childView);
    Q_ASSERT(pointView);

//    pointView->setAcceptHoverEvents(true);
    pointView->setParentItem(this);

    // polygon consisting from more than 2 points can be closed via hover event by clicking
    // on first polygon point
    if(childItems().size() > 2) {
        childItems()[0]->setAcceptHoverEvents(true);
    }


//    connect(childView, SIGNAL(xChanged()), this, SLOT(update_view()));
//    connect(childView, SIGNAL(yChanged()), this, SLOT(update_view()));
//    childView->setVisible(false);
    pointView->setVisible(true);

    update_polygon();

    connect(pointView, SIGNAL(propertyChanged()), this, SLOT(update_view()));
    connect(pointView, SIGNAL(closePolygonRequest(bool)), this, SLOT(onClosePolygonRequest(bool)));

}

QPointF PolygonView::getLastAddedPoint() const
{
    QPointF result;
    if(childItems().size()) {
        result = childItems().back()->scenePos();
    }
    return result;
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

void PolygonView::onClosePolygonRequest(bool value)
{
    m_close_polygon_request = value;
}

bool PolygonView::isClosedPolygon()
{
    qDebug() << "PolygonView::onClosePolygonRequest()";
    if(m_close_polygon_request) {
        foreach(QGraphicsItem *childItem, childItems()) {
            childItem->setFlag(QGraphicsItem::ItemIsMovable );
            childItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
            childItem->setAcceptHoverEvents(false);
            childItem->setCursor(Qt::SizeAllCursor);
        }
        m_closed_polygon = true;
    }
    return m_closed_polygon;
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

    painter->drawRect(m_bounding_rect);

    painter->drawPolyline(m_polygon.toPolygon());

    if(m_closed_polygon) {
        painter->drawPolygon(m_polygon.toPolygon());
    }

}

QVariant PolygonView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug() << "PolygonView::itemChange" << change << value << this->isSelected();
    if(change == QGraphicsItem::ItemSelectedHasChanged) {
        if(this->isSelected()) {
            setChildrenVisible(true);
        } else {
            setChildrenVisible(false);
        }
    }
    return value;
//    return QGraphicsItem::itemChange(change, value);

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
    update();
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
        qDebug() << "xxx 1.1 m_polygon" << m_polygon;

        QRectF scene_rect = m_polygon.boundingRect().marginsAdded(
            QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));
        qDebug() << "xxx 1.2 scene_rect" << scene_rect;

        m_bounding_rect = QRectF(0.0, 0.0, scene_rect.width(), scene_rect.height());
        qDebug() << "xxx 1.2 m_bounding_rect" << m_bounding_rect;

        setPos(scene_rect.x(), scene_rect.y());
        update();

        m_polygon = mapFromScene(m_polygon);


        qDebug() << "xxx 1.2 m_polygon" << m_polygon;

        for (int i = 0; i < childItems().size(); ++i) {
            QGraphicsItem *childView = childItems()[i];
            qDebug() << "!!!" << i << childView->isVisible();
//            disconnect(childView->toGraphicsObject(), SIGNAL(xChanged()), this,
//                       SLOT(update_view()));
//            disconnect(childView->toGraphicsObject(), SIGNAL(yChanged()), this,
//                       SLOT(update_view()));

            childView->setPos(m_polygon[i]);
//            childView->update();
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
    qDebug() << "PolygonView::update_polygon() 1.3 !!!!!" << m_polygon << m_polygon.size();

}

void PolygonView::update_points()
{
    qDebug() << "PolygonView::update_points()";
//    return;

    if(m_block_on_point_update) return;


//    m_block_on_point_update = true;
    foreach(QGraphicsItem *childItem, childItems()) {
        PolygonPointView *view = dynamic_cast<PolygonPointView *>(childItem);
//        ParameterizedItem *item = view->getParameterizedItem();
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

