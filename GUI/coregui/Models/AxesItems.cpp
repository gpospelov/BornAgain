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

const QString BasicAxisItem::P_IS_VISIBLE = "Visibility";
const QString BasicAxisItem::P_NBINS = "Nbins";
const QString BasicAxisItem::P_MIN = "Min";
const QString BasicAxisItem::P_MAX = "Max";
const QString BasicAxisItem::P_TITLE = "title";

BasicAxisItem::BasicAxisItem(const QString &type, ParameterizedItem *parent)
    : ParameterizedItem(type, parent)
{
    register_basic_properties();
}

void BasicAxisItem::register_basic_properties()
{
    registerProperty(P_IS_VISIBLE, true).setHidden();
    registerProperty(P_NBINS, 100).limited(1, 1024);
    registerProperty(P_MIN, 0.0).limitless().setDecimals(3);
    registerProperty(P_MAX, -1.0).limitless().setDecimals(3);
    registerProperty(P_TITLE, QString());
}

// ---------------------------------------------------------------------------------------------- //

const QString AmplitudeAxisItem::P_IS_LOGSCALE = "log10";
const QString AmplitudeAxisItem::P_LOCK_MIN_MAX = "Lock (min, max)";

AmplitudeAxisItem::AmplitudeAxisItem(ParameterizedItem *parent)
    : BasicAxisItem(Constants::AmplitudeAxisType, parent)
{
    registerProperty(P_LOCK_MIN_MAX, false).setHidden();
    registerProperty(P_IS_LOGSCALE, true);
    setPropertyAppearance(BasicAxisItem::P_TITLE, PropertyAttribute::HIDDEN);
//    getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    setPropertyAppearance(BasicAxisItem::P_IS_VISIBLE, PropertyAttribute::VISIBLE);
}
