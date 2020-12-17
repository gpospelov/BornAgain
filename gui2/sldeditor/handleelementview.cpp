//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/handleelementview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/sldeditor/handleelementview.h"
#include "gui2/sldeditor/layerelementcontroller.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

namespace gui2 {

//! The constructor
HandleElementView::HandleElementView()
    : ElementView()
    , m_pos(QPointF(0, 0))
    , m_rectangle(QRectF(0, 0, 0, 0))
    , m_brush(QBrush())
    , m_pen(QPen()) {
    adaptW(false);
    adaptH(false);
    setZValue(2);
}

//! The overriden paint method
void HandleElementView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setClipRect(sceneAdapter()->viewportRectangle());
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawEllipse(displayRect(m_rectangle));
}

//! The shape
QPainterPath HandleElementView::shape() const {
    QPainterPath path;
    path.addRect(displayRect(m_rectangle));
    return path;
}

//! The bounding rectangle of the handle
QRectF HandleElementView::boundingRect() const {
    return displayRect(m_rectangle);
}

//! On move update the model
void HandleElementView::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    m_pos = scenePos(event->pos());
    p_controller->handleViewMoved(this);
}

//! Set the controller to report back the move
void HandleElementView::setLayerElementController(LayerElementController* controller) {
    p_controller = controller;
}

//! Set the draw rectangle
void HandleElementView::setRectangle(QRectF rectangle) {
    prepareGeometryChange();
    m_rectangle = rectangle;
}

//! Set the brush
void HandleElementView::setBrush(QBrush brush) {
    m_brush = brush;
}

//! Set the pen
void HandleElementView::setPen(QPen pen) {
    m_pen = pen;
}

//! Get the last position of the item
QPointF HandleElementView::getLastPos() const {
    return m_pos;
}

} // namespace gui2
