// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/RegionOfInterestView.h
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

void RegionOfInterestView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(QPen(QColor(34, 67, 255)));
    painter->drawRect(m_mask_rect);
}
