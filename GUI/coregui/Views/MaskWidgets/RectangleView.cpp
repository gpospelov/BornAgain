// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/IMaskView.h
//! @brief     Implements interface class IMaskView for all masks on graphics scene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RectangleView.h"
#include "MaskItems.h"
#include "DesignerHelper.h"
#include <QPainter>

RectangleView::RectangleView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

}

QRectF RectangleView::boundingRect() const
{
    return QRectF(0.0, 0.0,
                  toSceneX(RectangleItem::P_WIDTH), toSceneY(RectangleItem::P_HEIGHT));
}

void RectangleView::setParameterizedItem(ParameterizedItem *item)
{
    IMaskView::setParameterizedItem(item);
    setX(toSceneX(RectangleItem::P_POSX));
    setY(toSceneY(RectangleItem::P_POSY));
}

void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->setRenderHints(QPainter::Antialiasing);
    prepareGeometryChange();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(DesignerHelper::getDefaultColor("Transparant red"));
    painter->setPen(brush.color().darker());
    painter->setBrush(brush);
    painter->drawRect(boundingRect());
}
