// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/RegionOfInterestView.cpp
//! @brief     Defines RegionOfInterestView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RegionOfInterestView.h"
#include <QPainter>

//! Paints two-color tiny frame without filling.

void RegionOfInterestView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(QColor(34, 67, 255)));
    painter->drawRect(m_mask_rect);

    QRectF secondRect = m_mask_rect.marginsAdded(QMarginsF(1, 1, 1, 1));
    painter->setPen(QPen(QColor(255, 255, 245)));
    painter->drawRect(secondRect);
}
