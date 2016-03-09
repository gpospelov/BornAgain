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

MagneticFieldItem::MagneticFieldItem()
    : SessionItem(Constants::MagneticFieldType)
{
    addProperty(P_BX, 0.0);
    addProperty(P_BY, 0.0);
    addProperty(P_BZ, 0.0);
}

QString MagneticFieldItem::itemLabel() const
{
    return QString("(%1, %2, %3)").arg(getChildValue(P_BX).toDouble())
                                  .arg(getChildValue(P_BY).toDouble())
                                  .arg(getChildValue(P_BZ).toDouble());
}
