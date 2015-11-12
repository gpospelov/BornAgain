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
#include <QPainter>

PolygonPointView::PolygonPointView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable );
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF PolygonPointView::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}

void PolygonPointView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();
    painter->setBrush(MaskEditorHelper::getSelectionMarkerBrush());
    painter->setPen(MaskEditorHelper::getSelectionMarkerPen());
    painter->drawEllipse(boundingRect());
}

