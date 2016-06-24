// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/AxesItems.cpp
//! @brief     Implements various axis items
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "AxesItems.h"

const QString BasicAxisItem::P_IS_VISIBLE = "Visibility";
const QString BasicAxisItem::P_NBINS = "Nbins";
const QString BasicAxisItem::P_MIN = "Min";
const QString BasicAxisItem::P_MAX = "Max";
const QString BasicAxisItem::P_TITLE = "title";
//const QString BasicAxisItem::P_TITLE_IS_VISIBLE = "Title Visibility";

static const int max_detector_pixels = 65536;

BasicAxisItem::BasicAxisItem(const QString &type)
    : SessionItem(type)
{
    register_basic_properties();
}

//bool BasicAxisItem::isAxisLabelVisible() const
//{
//    return getItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE).toBool();
//}

void BasicAxisItem::register_basic_properties()
{
    addProperty(P_IS_VISIBLE, true)->setVisible(false);
    addProperty(P_NBINS, 100)->setLimits(AttLimits::limited(1, max_detector_pixels));
    addProperty(P_MIN, 0.0)->setDecimals(3);
    getItem(P_MIN)->setLimits(AttLimits::limitless());
    addProperty(P_MAX, -1.0)->setDecimals(3);
    getItem(P_MAX)->setLimits(AttLimits::limitless());
    addProperty(P_TITLE, QString());
    addProperty(P_TITLE_IS_VISIBLE, false);
}

// ---------------------------------------------------------------------------------------------- //

const QString AmplitudeAxisItem::P_IS_LOGSCALE = "log10";
const QString AmplitudeAxisItem::P_LOCK_MIN_MAX = "Lock (min, max)";

AmplitudeAxisItem::AmplitudeAxisItem()
    : BasicAxisItem(Constants::AmplitudeAxisType)
{
    addProperty(P_LOCK_MIN_MAX, false)->setVisible(false);
    addProperty(P_IS_LOGSCALE, true);
    getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    getItem(BasicAxisItem::P_IS_VISIBLE)->setVisible(true);
}
