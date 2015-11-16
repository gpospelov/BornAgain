// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/PolygonPointView.cpp
//! @brief     Implements PolygonPointView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PolygonPointView.h"
#include "MaskEditorHelper.h"
#include "MaskItems.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>

PolygonPointView::PolygonPointView()
    : m_on_hover(false)
//    , m_first_polygon_point(false)
//    : m_block_on_property_change(false)
{
//    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
//    setAcceptHoverEvents(false);
    //setCursor(Qt::SizeAllCursor);
}

QRectF PolygonPointView::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}

void PolygonPointView::updateParameterizedItem(const QPointF &pos)
{
//    if(m_block_on_property_change) return;

//    m_block_on_property_change = true;
    m_item->setRegisteredProperty(PolygonPointItem::P_POSX, fromSceneX(pos.x()));
    m_item->setRegisteredProperty(PolygonPointItem::P_POSY, fromSceneY(pos.y()));
    //    m_block_on_property_change = false;
}

//void PolygonPointView::setFirstPolygonPointFlag(bool value)
//{
//    m_first_polygon_point = value;
//    setAcceptHoverEvents(m_first_polygon_point);
//}

//void PolygonPointView::setIsFirstPolygonPoint(bool value)
//{
//    m_first_polygon_point = value;

//}


void PolygonPointView::onChangedX()
{
    qDebug() << "PolygonPointView::onChangedX()" << m_item->modelType() << x();
//    m_block_on_property_change = true;
////    m_item->setRegisteredProperty(PolygonPointItem::P_POSX, fromSceneX(this->scenePos().x()));
//    m_item->setRegisteredProperty(PolygonPointItem::P_POSX, fromSceneX(this->x()));
//    m_block_on_property_change = false;
}

void PolygonPointView::onChangedY()
{
    qDebug() << "PolygonPointView::onChangedY()" << m_item->modelType() << x();
//    m_block_on_property_change = true;
////    m_item->setRegisteredProperty(PolygonPointItem::P_POSY, fromSceneY(this->scenePos().y()));
//    m_item->setRegisteredProperty(PolygonPointItem::P_POSY, fromSceneY(this->y()));
//    m_block_on_property_change = false;
}

//void PolygonPointView::onPropertyChange(const QString &propertyName)
//{
//    if(m_block_on_property_change) return;

////    if(propertyName == PolygonPointItem::P_POSX || propertyName == PolygonPointItem::P_POSY) {
////        QPointF scenePos(toSceneX(PolygonPointItem::P_POSX), toSceneY(PolygonPointItem::P_POSY));
////        QPointF itemPos = mapFromScene(scenePos);
////        setPos(itemPos);
////    }

//    if(propertyName == PolygonPointItem::P_POSX) {
//        setX(toSceneX(PolygonPointItem::P_POSX));
//    }
//    else if(propertyName == PolygonPointItem::P_POSY) {
//        setY(toSceneY(PolygonPointItem::P_POSY));
//    }
//}

void PolygonPointView::update_view()
{
//    update_position();
    update();
}


void PolygonPointView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();
    QBrush brush = MaskEditorHelper::getSelectionMarkerBrush();
    if(m_on_hover) {
        brush.setColor(Qt::red);
    }
    painter->setBrush(brush);
    painter->setPen(MaskEditorHelper::getSelectionMarkerPen());
    painter->drawEllipse(boundingRect());
}

void PolygonPointView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "PolygonPointView::mouseMoveEvent()";
//    setX(event->scenePos().x());
//    setY(event->scenePos().y());
//    setPos(mapFromScene(event->scenePos()));

    updateParameterizedItem(event->scenePos());
//    update_view();
//    IMaskView::mouseMoveEvent(event);

}

QVariant PolygonPointView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qDebug() << "PolygonPointView::itemChange" << change;
    return QGraphicsItem::itemChange(change, value);
}

void PolygonPointView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "PolygonPointView::mousePressEvent";
    IMaskView::mousePressEvent(event);
    if(acceptHoverEvents()) {
        m_on_hover = false;
        emit closePolygonRequest();
    }
}

void PolygonPointView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "PolygonPointView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)";
    Q_UNUSED(event);
    m_on_hover = true;
    IMaskView::hoverEnterEvent(event);
}

void PolygonPointView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "PolygonPointView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)";
    Q_UNUSED(event);
    m_on_hover = false;
    IMaskView::hoverLeaveEvent(event);
}


void PolygonPointView::update_position()
{
//    qDebug() << "PolygonPointView::update_position()";
//    setX(toSceneX(PolygonPointItem::P_POSX));
//    setY(toSceneY(PolygonPointItem::P_POSY));

//    QPointF pos(toSceneX(PolygonPointItem::P_POSX), toSceneY(PolygonPointItem::P_POSY));
//    if(parentItem()) {
//        setPos(parentItem()->mapFromScene(pos));
//    }

}

