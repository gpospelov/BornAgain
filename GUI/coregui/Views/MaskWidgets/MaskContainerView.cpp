// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskContainerView.cpp
//! @brief     Implements MaskContainerView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskContainerView.h"
#include "ISceneAdaptor.h"
#include <QBrush>
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

MaskContainerView::MaskContainerView()
{
    // the key flag to not to draw children going outside ot given shape
    setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
}

void MaskContainerView::update_view()
{
    m_bounding_rect = m_adaptor->getViewportRectangle();
    update();
}

void MaskContainerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_UNUSED(painter);
}
