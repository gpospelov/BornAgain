// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/AxesItems.cpp
//! @brief     Implements various axis items
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AxesItems.h"

const QString BasicAxisItem::P_MIN = "min";
const QString BasicAxisItem::P_MAX = "max";
const QString BasicAxisItem::P_TITLE = "title";

BasicAxisItem::BasicAxisItem(const QString &type, ParameterizedItem *parent)
    : ParameterizedItem(type, parent)
{
    setItemName(type);
    registerProperty(P_MIN, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_MAX, -1.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_TITLE, QString());


}

const QString AmplitudeAxisItem::P_IS_LOGSCALE = "log10";

AmplitudeAxisItem::AmplitudeAxisItem(ParameterizedItem *parent)
    : BasicAxisItem(Constants::AmplitudeAxisType, parent)
{
    registerProperty(P_IS_LOGSCALE, true);
    setPropertyAppearance(BasicAxisItem::P_TITLE, PropertyAttribute::HIDDEN);
}
