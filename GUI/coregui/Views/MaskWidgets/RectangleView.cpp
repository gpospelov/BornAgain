// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/RectangleView.cpp
//! @brief     Implements RectangleView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RectangleView.h"
#include "MaskItems.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

RectangleView::RectangleView()
{
}

void RectangleView::onChangedX()
{
    m_block_on_property_change = true;
    m_item->setItemValue(RectangleItem::P_XLOW, fromSceneX(this->x()));
    m_item->setItemValue(RectangleItem::P_XUP, fromSceneX(this->x() + m_mask_rect.width()));
    m_block_on_property_change = false;
}

void RectangleView::onChangedY()
{
    m_block_on_property_change = true;
    m_item->setItemValue(RectangleItem::P_YLOW, fromSceneY(this->y() + m_mask_rect.height()));
    m_item->setItemValue(RectangleItem::P_YUP, fromSceneY(this->y()));
    m_block_on_property_change = false;
}

void RectangleView::onPropertyChange(const QString &propertyName)
{
    if(m_block_on_property_change) return;

    if(propertyName == MaskItem::P_MASK_VALUE) {
        update();
    } else {
        update_view();
    }
}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawRect(m_mask_rect);
}

void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_activeHandleElement) {

        qreal xmin = std::min(event->scenePos().x(),m_resize_opposite_origin.x());
        qreal xmax = std::max(event->scenePos().x(),m_resize_opposite_origin.x());
        qreal ymin = std::min(event->scenePos().y(),m_resize_opposite_origin.y());
        qreal ymax = std::max(event->scenePos().y(),m_resize_opposite_origin.y());

        if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE) {
            m_item->setItemValue(RectangleItem::P_XLOW, fromSceneX(xmin));
            m_item->setItemValue(RectangleItem::P_YLOW, fromSceneY(ymax));
            m_item->setItemValue(RectangleItem::P_XUP, fromSceneX(xmax));
            m_item->setItemValue(RectangleItem::P_YUP, fromSceneY(ymin));

        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_HEIGHT) {
            m_item->setItemValue(RectangleItem::P_YLOW, fromSceneY(ymax));
            m_item->setItemValue(RectangleItem::P_YUP, fromSceneY(ymin));

        } else if(m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_WIDTH) {

            m_item->setItemValue(RectangleItem::P_XLOW, fromSceneX(xmin));
            m_item->setItemValue(RectangleItem::P_XUP, fromSceneX(xmax));

        }
        update_view();

    } else {
        IMaskView::mouseMoveEvent(event);
    }
}

//! updates position of view using item properties
void RectangleView::update_position()
{
    setX(toSceneX(RectangleItem::P_XLOW));
    setY(toSceneY(RectangleItem::P_YUP));    
}

QRectF RectangleView::mask_rectangle()
{
    return QRectF(0.0, 0.0, width(), height());
}

//! returns the x-coordinate of the rectangle's left edge

qreal RectangleView::left() const
{
    return toSceneX(par(RectangleItem::P_XLOW));
}

//! returns the x-coordinate of the rectangle's right edge

qreal RectangleView::right() const
{
    return toSceneX(par(RectangleItem::P_XUP));
}

//! Returns the y-coordinate of the rectangle's top edge.

qreal RectangleView::top() const
{
    return toSceneY(par(RectangleItem::P_YUP));
}

//! Returns the y-coordinate of the rectangle's bottom edge.

qreal RectangleView::bottom() const
{
    return toSceneY(par(RectangleItem::P_YLOW));
}

