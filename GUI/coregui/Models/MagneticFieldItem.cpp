// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MagneticFieldItem.cpp
//! @brief     Implements class MagneticFieldItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MagneticFieldItem.h"

const QString MagneticFieldItem::P_BX = "Bx";
const QString MagneticFieldItem::P_BY = "By";
const QString MagneticFieldItem::P_BZ = "Bz";

MagneticFieldItem::MagneticFieldItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::MagneticFieldType, parent)
{
    setItemName(Constants::MagneticFieldType);
    registerProperty(P_BX, 0.0);
    registerProperty(P_BY, 0.0);
    registerProperty(P_BZ, 0.0);
}

QString MagneticFieldItem::itemLabel() const
{
    return QString("(%1, %2, %3)").arg(getRegisteredProperty(P_BX).toDouble())
                                  .arg(getRegisteredProperty(P_BY).toDouble())
                                  .arg(getRegisteredProperty(P_BZ).toDouble());
}



