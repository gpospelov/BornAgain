// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskContainerView.cpp
//! @brief     Implements MaskContainerView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskContainerView.h"
#include "ISceneAdaptor.h"
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QDebug>


MaskContainerView::MaskContainerView()
{
    // the key flag to not to draw children going outside ot given shape
    setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
}

void MaskContainerView::update_view()
{
//    prepareGeometryChange();
    m_bounding_rect = m_adaptor->getViewportRectangle();
    update();
}

void MaskContainerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_UNUSED(painter);
}
