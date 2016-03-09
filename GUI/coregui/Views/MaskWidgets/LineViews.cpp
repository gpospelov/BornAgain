// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/LineViews.cpp
//! @brief     Implements classes VerticalLineView and HorizontalLineView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LineViews.h"
#include "MaskItems.h"
#include "MaskEditorHelper.h"
#include "ColorMapSceneAdaptor.h"
#include <QPainter>
#include <QCursor>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

namespace {
const double mask_width = 8.0;
const double mask_visible_width = 3.0;
}

VerticalLineView::VerticalLineView()
    : m_block_on_property_change(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setCursor(Qt::SizeHorCursor);
}

void VerticalLineView::onChangedX()
{
    m_block_on_property_change = true;
    m_item->setItemValue(VerticalLineItem::P_POSX, fromSceneX(this->x()));
    m_block_on_property_change = false;
}

void VerticalLineView::onPropertyChange(const QString &propertyName)
{
    if(m_block_on_property_change) return;
    if(propertyName == VerticalLineItem::P_POSX) {
        setX(toSceneX(VerticalLineItem::P_POSX));
    }
}

void VerticalLineView::update_view()
{
    QRectF plot_scene_rectangle = m_adaptor->getViewportRectangle();

    setX(toSceneX(VerticalLineItem::P_POSX));
    setY(plot_scene_rectangle.top());

    m_bounding_rect = QRectF(-mask_width/2., 0.0, mask_width, plot_scene_rectangle.height());
    update();
}

void VerticalLineView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawRect(QRectF(-mask_visible_width/2., 0.0, mask_visible_width,
                             m_bounding_rect.height()));

    if(isSelected()) {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRectF(-mask_visible_width/2., 0.0, mask_visible_width,
                                 m_bounding_rect.height()));
    }
}

//! Allows item movement along x, prevent movement along y
QVariant VerticalLineView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (isSelected() && change == ItemPositionChange && scene()) {
          QPointF newPos = value.toPointF();
          newPos.setY(y());
          return newPos;
      }
    return QGraphicsItem::itemChange(change, value);
}

// ------------------------------------------------------------------------- //

HorizontalLineView::HorizontalLineView()
    : m_block_on_property_change(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setCursor(Qt::SizeVerCursor);
}

void HorizontalLineView::onChangedY()
{
    m_block_on_property_change = true;
    m_item->setItemValue(HorizontalLineItem::P_POSY, fromSceneY(this->y()));
    m_block_on_property_change = false;
}

void HorizontalLineView::onPropertyChange(const QString &propertyName)
{
    if(m_block_on_property_change) return;
    if(propertyName == HorizontalLineItem::P_POSY) {
        setY(toSceneY(HorizontalLineItem::P_POSY));
    }
}

void HorizontalLineView::update_view()
{
    QRectF plot_scene_rectangle = m_adaptor->getViewportRectangle();

    setX(plot_scene_rectangle.left());
    setY(toSceneY(HorizontalLineItem::P_POSY));

    m_bounding_rect = QRectF(0.0, -mask_width/2., plot_scene_rectangle.width(), mask_width);
    update();
}

void HorizontalLineView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawRect(QRectF( 0.0, -mask_visible_width/2., m_bounding_rect.width(),
                              mask_visible_width));

    if(isSelected()) {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QRectF(0.0, -mask_visible_width/2., m_bounding_rect.width(),
                                 mask_visible_width));
    }
}

//! Allows item movement along y, prevent movement along x
QVariant HorizontalLineView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (isSelected() && change == ItemPositionChange && scene()) {
          QPointF newPos = value.toPointF();
          newPos.setX(x());
          return newPos;
      }
    return QGraphicsItem::itemChange(change, value);
}
