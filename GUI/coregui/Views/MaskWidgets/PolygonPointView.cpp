// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/PolygonPointView.cpp
//! @brief     Implements PolygonPointView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PolygonPointView.h"
#include "ISceneAdaptor.h"
#include "MaskEditorHelper.h"
#include "MaskItems.h"
#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

PolygonPointView::PolygonPointView()
    : m_on_hover(false)
{
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF PolygonPointView::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}

void PolygonPointView::updateParameterizedItem(const QPointF &pos)
{
    m_item->setItemValue(PolygonPointItem::P_POSX, fromSceneX(pos.x()));
    m_item->setItemValue(PolygonPointItem::P_POSY, fromSceneY(pos.y()));
}

void PolygonPointView::update_view()
{
    update();
}

void PolygonPointView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    QBrush brush = MaskEditorHelper::getSelectionMarkerBrush();
    if(acceptHoverEvents() && m_on_hover) {
        brush.setColor(Qt::red);
    }
    painter->setBrush(brush);
    painter->setPen(MaskEditorHelper::getSelectionMarkerPen());
    painter->drawEllipse(boundingRect());
}

void PolygonPointView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    updateParameterizedItem(event->scenePos());
}

void PolygonPointView::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_on_hover = true;
    emit closePolygonRequest(m_on_hover);
    IMaskView::hoverEnterEvent(event);
}

void PolygonPointView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_on_hover = false;
    emit closePolygonRequest(m_on_hover);
    IMaskView::hoverLeaveEvent(event);
}
