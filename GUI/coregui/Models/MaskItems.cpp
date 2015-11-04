// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MaskItems.cpp
//! @brief     Implements MaskItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskItems.h"

/* ------------------------------------------------ */
const QString RectangleItem::P_POSX = "X position";
const QString RectangleItem::P_POSY = "Y position";
const QString RectangleItem::P_WIDTH = "Width";
const QString RectangleItem::P_HEIGHT = "Height";

RectangleItem::RectangleItem(ParameterizedItem *parent)
    : MaskItem(Constants::RectangleMaskType, parent)
{
    setItemName(Constants::RectangleMaskType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
}
