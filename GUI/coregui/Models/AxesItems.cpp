//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/AxesItems.cpp
//! @brief     Implements various axis items
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/AxesItems.h"
#include "Base/Axis/FixedBinAxis.h"

const QString BasicAxisItem::P_IS_VISIBLE = "Visibility";
const QString BasicAxisItem::P_NBINS = "Nbins";
const QString BasicAxisItem::P_MIN_DEG = "Min [deg]";
const QString BasicAxisItem::P_MAX_DEG = "Max [deg]";
const QString BasicAxisItem::P_TITLE = "Title";
const QString BasicAxisItem::P_TITLE_IS_VISIBLE = "Title Visibility";

const int max_detector_pixels = 65536;

BasicAxisItem::BasicAxisItem(const QString& type) : SessionItem(type)
{
    register_basic_properties();
}

int BasicAxisItem::binCount() const
{
    return getItemValue(P_NBINS).toInt();
}

void BasicAxisItem::setBinCount(int value)
{
    setItemValue(P_NBINS, value);
}

double BasicAxisItem::lowerBound() const
{
    return getItemValue(P_MIN_DEG).toDouble();
}

void BasicAxisItem::setLowerBound(double value)
{
    setItemValue(P_MIN_DEG, value);
}

double BasicAxisItem::upperBound() const
{
    return getItemValue(P_MAX_DEG).toDouble();
}

void BasicAxisItem::setUpperBound(double value)
{
    setItemValue(P_MAX_DEG, value);
}

QString BasicAxisItem::title() const
{
    return getItemValue(P_TITLE).toString();
}

void BasicAxisItem::setTitle(const QString& title)
{
    setItemValue(P_TITLE, title);
}

std::unique_ptr<IAxis> BasicAxisItem::createAxis(double scale) const
{
    return std::make_unique<FixedBinAxis>(title().toStdString(), binCount(), lowerBound() * scale,
                                          upperBound() * scale);
}

BasicAxisItem::~BasicAxisItem() = default;

void BasicAxisItem::register_basic_properties()
{
    addProperty(P_IS_VISIBLE, true)->setVisible(false);
    addProperty(P_NBINS, 100)->setLimits(RealLimits::limited(1, max_detector_pixels));
    addProperty(P_MIN_DEG, 0.0)->setDecimals(3).setLimits(RealLimits::limitless());
    addProperty(P_MAX_DEG, -1.0)->setDecimals(3).setLimits(RealLimits::limitless());
    addProperty(P_TITLE, QString());
    addProperty(P_TITLE_IS_VISIBLE, true)->setVisible(false);
}

// ---------------------------------------------------------------------------------------------- //

const QString AmplitudeAxisItem::P_IS_LOGSCALE = "log10";
const QString AmplitudeAxisItem::P_LOCK_MIN_MAX = "Lock (min, max)";

AmplitudeAxisItem::AmplitudeAxisItem() : BasicAxisItem("AmplitudeAxis")
{
    addProperty(P_LOCK_MIN_MAX, false)->setVisible(false);
    addProperty(P_IS_LOGSCALE, true);
    getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    getItem(BasicAxisItem::P_IS_VISIBLE)->setVisible(true);
    setMinMaxEditor("ScientificDouble");

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_IS_LOGSCALE) {
            if (getItemValue(P_IS_LOGSCALE).toBool())
                setMinMaxEditor("ScientificDouble");
            else
                setMinMaxEditor("Default");
        }
    });
}

bool AmplitudeAxisItem::isLogScale() const
{
    return getItemValue(P_IS_LOGSCALE).toBool();
}

void AmplitudeAxisItem::setLogScale(bool value)
{
    setItemValue(P_IS_LOGSCALE, value);
}

//! Sets editor for min, max values of axes

void AmplitudeAxisItem::setMinMaxEditor(const QString& editorType)
{
    getItem(BasicAxisItem::P_MIN_DEG)->setEditorType(editorType);
    getItem(BasicAxisItem::P_MAX_DEG)->setEditorType(editorType);
}
