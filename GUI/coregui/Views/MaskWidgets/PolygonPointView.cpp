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
#include <QDebug>

PolygonPointView::PolygonPointView()
    : m_block_on_property_change(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF PolygonPointView::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}


void PolygonPointView::onChangedX()
{
    qDebug() << "PolygonPointView::onChangedX()" << m_item->modelType() << x();
    m_block_on_property_change = true;
    m_item->setRegisteredProperty(PolygonPointItem::P_POSX, fromSceneX(this->x()));
    m_block_on_property_change = false;
}

void PolygonPointView::onChangedY()
{
    qDebug() << "PolygonPointView::onChangedY()" << m_item->modelType() << x();
    m_block_on_property_change = true;
    m_item->setRegisteredProperty(PolygonPointItem::P_POSY, fromSceneY(this->y()));
    m_block_on_property_change = false;
}

void PolygonPointView::onPropertyChange(const QString &propertyName)
{
    if(m_block_on_property_change) return;

    else if(propertyName == PolygonPointItem::P_POSX) {
        setX(toSceneX(PolygonPointItem::P_POSX));
    }
    else if(propertyName == PolygonPointItem::P_POSY) {
        setY(toSceneY(PolygonPointItem::P_POSY));
    }
}

void PolygonPointView::update_view()
{
    update_position();
    update();
}


void PolygonPointView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();
    painter->setBrush(MaskEditorHelper::getSelectionMarkerBrush());
    painter->setPen(MaskEditorHelper::getSelectionMarkerPen());
    painter->drawEllipse(boundingRect());
}

void PolygonPointView::update_position()
{
    setX(toSceneX(PolygonPointItem::P_POSX));
    setY(toSceneY(PolygonPointItem::P_POSY));
}

