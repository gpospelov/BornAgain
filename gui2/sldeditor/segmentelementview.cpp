//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/segmentelementview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/sldeditor/segmentelementview.h"
#include "gui2/sldeditor/layerelementcontroller.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

namespace gui2 {

//! The constructor
SegmentElementView::SegmentElementView()
    : ElementView()
    , m_pos(QPointF(0, 0))
    , m_rectangle(QRectF(0, 0, 0, 0))
    , m_brush(QBrush())
    , m_pen(QPen()) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setZValue(1);
}

//! The overriden paint method
void SegmentElementView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setClipRect(sceneAdapter()->viewportRectangle());
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(displayRect(m_rectangle));
}

//! The shape
QPainterPath SegmentElementView::shape() const {
    QPainterPath path;
    path.addRect(displayRect(m_rectangle));
    return path;
}

//! The bounding rectangle of the handle
QRectF SegmentElementView::boundingRect() const {
    return displayRect(m_rectangle);
}

//! On move save the new position and notify the controller
void SegmentElementView::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    m_pos = scenePos(event->pos());
    p_controller->segmentViewMoved(this);
}

//! Set the controller to report back the move
void SegmentElementView::setLayerElementController(LayerElementController* controller) {
    p_controller = controller;
}

//! Set the draw rectangle
void SegmentElementView::setRectangle(QRectF rectangle) {
    prepareGeometryChange();
    m_rectangle = rectangle;
}

//! Set the brush
void SegmentElementView::setBrush(QBrush brush) {
    m_brush = brush;
}

//! Set the pen
void SegmentElementView::setPen(QPen pen) {
    m_pen = pen;
}

//! Get the last position of the item
QPointF SegmentElementView::getLastPos() const {
    return m_pos;
}

} // namespace gui2
