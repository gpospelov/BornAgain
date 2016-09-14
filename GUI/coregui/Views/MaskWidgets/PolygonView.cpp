// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/PolygonView.cpp
//! @brief     Implements PolygonView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PolygonView.h"
#include "MaskEditorHelper.h"
#include "MaskItems.h"
#include "PolygonPointView.h"
#include "ISceneAdaptor.h"
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
    , m_close_polygon_request(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void PolygonView::addView(IMaskView *childView, int row)
{
    Q_UNUSED(row);

    if(childItems().contains(childView)) return;

    PolygonPointView *pointView = dynamic_cast<PolygonPointView *>(childView);
    Q_ASSERT(pointView);
    pointView->setParentItem(this);

    // polygon consisting from more than 2 points can be closed via hover event by clicking
    // on first polygon point
    if(!isClosedPolygon() && childItems().size() > 2) {
        childItems()[0]->setAcceptHoverEvents(true);
    }

    pointView->setVisible(true);
    update_polygon();

    connect(pointView, SIGNAL(propertyChanged()), this, SLOT(update_view()));
    connect(pointView, SIGNAL(closePolygonRequest(bool)), this, SLOT(onClosePolygonRequest(bool)));
}

//! returns last added poligon point in scene coordinates
QPointF PolygonView::getLastAddedPoint() const
{
    QPointF result;
    if(childItems().size()) {
        result = childItems().back()->scenePos();
    }
    return result;
}

//! Returns true if there was a request to close polygon (emitted by its start point),
//! and then closes a polygon. Returns true if polygon was closed.
bool PolygonView::closePolygonIfNecessary()
{
    if(m_close_polygon_request) {
        foreach(QGraphicsItem *childItem, childItems()) {
            childItem->setFlag(QGraphicsItem::ItemIsMovable );
            childItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
            childItem->setAcceptHoverEvents(false);
            childItem->setCursor(Qt::SizeAllCursor);
        }
        m_item->setItemValue(PolygonItem::P_ISCLOSED, true);
        update();
    }
    return isClosedPolygon();
}

void PolygonView::onClosePolygonRequest(bool value)
{
    m_close_polygon_request = value;
}

bool PolygonView::isClosedPolygon()
{
    return m_item->getItemValue(PolygonItem::P_ISCLOSED).toBool();
}

void PolygonView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_ASSERT(m_item);
    painter->setRenderHints(QPainter::Antialiasing);

    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));

    // painter->drawRect(m_bounding_rect);

    painter->drawPolyline(m_polygon.toPolygon());

    if(isClosedPolygon()) {
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
}

void PolygonView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    IMaskView::mouseMoveEvent(event);
    update_points();
}

void PolygonView::update_view()
{
//    prepareGeometryChange();
    update_polygon();
    update();
}

//! Runs through all PolygonPointItem and calculate bounding rectangle.
//! Determines position of the rectangle in scene.
//! Calculates position of PolygonPointView in local polygon coordinates
void PolygonView::update_polygon()
{
    if(m_block_on_point_update) return;

    m_block_on_point_update = true;

    if (m_item->rowCount()) {

        m_polygon.clear();

        foreach (SessionItem *item, m_item->getChildrenOfType(Constants::PolygonPointType)) {
            qreal px = toSceneX(item->getItemValue(PolygonPointItem::P_POSX).toReal());
            qreal py = toSceneY(item->getItemValue(PolygonPointItem::P_POSY).toReal());
            m_polygon << QPointF(px, py);
        }

        QRectF scene_rect = m_polygon.boundingRect().marginsAdded(
            QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));

        m_bounding_rect = QRectF(0.0, 0.0, scene_rect.width(), scene_rect.height());

        setPos(scene_rect.x(), scene_rect.y());
        update(); // to propagate changes to scene

        m_polygon = mapFromScene(m_polygon);

        for (int i = 0; i < childItems().size(); ++i) {
            QGraphicsItem *childView = childItems()[i];
            childView->setPos(m_polygon[i]);
        }

        setPos(scene_rect.x(), scene_rect.y());
    }

    m_block_on_point_update = false;
}

//! When polygon moves as a whole thing accross the scene, given method updates coordinates
//! of PolygonPointItem's
void PolygonView::update_points()
{
    if(m_block_on_point_update) return;

    foreach(QGraphicsItem *childItem, childItems()) {
        PolygonPointView *view = dynamic_cast<PolygonPointView *>(childItem);
        QPointF pos = view->scenePos();
        disconnect(view, SIGNAL(propertyChanged()), this, SLOT(update_view()));
        view->updateParameterizedItem(pos);
        connect(view, SIGNAL(propertyChanged()), this, SLOT(update_view()));
   }
}

void PolygonView::setChildrenVisible(bool value)
{
    foreach(QGraphicsItem *childItem, childItems()) {
        childItem->setVisible(value);
    }
}