// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/VectorItem.cpp
//! @brief     Implements class VectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "VectorItem.h"

const QString VectorItem::P_X = "X";
const QString VectorItem::P_Y = "Y";
const QString VectorItem::P_Z = "Z";

VectorItem::VectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::VectorType, parent)
{
    setItemName(Constants::VectorType);
    registerProperty(P_X, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_Y, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_Z, 0.0, PropertyAttribute(AttLimits::limitless()));
}

QString VectorItem::itemLabel() const
{
    return QString("(%1, %2, %3)").arg(getRegisteredProperty(P_X).toDouble())
                                  .arg(getRegisteredProperty(P_Y).toDouble())
                                  .arg(getRegisteredProperty(P_Z).toDouble());
}

