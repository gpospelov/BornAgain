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

VectorItem::VectorItem()
    : ParameterizedItem(Constants::VectorType)
{
    registerProperty(P_X, 0.0).limitless();
    registerProperty(P_Y, 0.0).limitless();
    registerProperty(P_Z, 0.0).limitless();
}

QString VectorItem::label() const
{
    return QString("(%1, %2, %3)").arg(getRegisteredProperty(P_X).toDouble())
                                  .arg(getRegisteredProperty(P_Y).toDouble())
            .arg(getRegisteredProperty(P_Z).toDouble());
}

kvector_t VectorItem::getVector() const
{
    return kvector_t(getRegisteredProperty(P_X).toDouble(),
                     getRegisteredProperty(P_Y).toDouble(),
                     getRegisteredProperty(P_Z).toDouble());
}

