// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NIntensityDataItem.cpp
//! @brief     Implements class NIntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "NIntensityDataItem.h"
#include "ComboProperty.h"
#include "AngleProperty.h"

const QString NIntensityDataItem::P_XAXIS_MIN = "xmin";
const QString NIntensityDataItem::P_XAXIS_MAX = "xmax";
const QString NIntensityDataItem::P_YAXIS_MIN = "ymin";
const QString NIntensityDataItem::P_YAXIS_MAX = "ymax";
const QString NIntensityDataItem::P_ZAXIS_MIN = "zmin";
const QString NIntensityDataItem::P_ZAXIS_MAX = "zmax";
const QString NIntensityDataItem::P_GRADIENT = "Gradient";
const QString NIntensityDataItem::P_IS_LOGZ = "Logz";
const QString NIntensityDataItem::P_IS_INTERPOLATED = "Interpolation";
const QString NIntensityDataItem::P_XAXIS_TITLE = "x-title";
const QString NIntensityDataItem::P_YAXIS_TITLE = "y-title";
const QString NIntensityDataItem::P_AXES_UNITS = "Axes Units";

NIntensityDataItem::NIntensityDataItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::IntensityDataType, parent)
{
    setItemName(Constants::IntensityDataType);
    registerProperty(P_XAXIS_MIN, 0.0);
    registerProperty(P_XAXIS_MAX, 0.0);
    registerProperty(P_YAXIS_MIN, 0.0);
    registerProperty(P_YAXIS_MAX, 0.0);
    registerProperty(P_ZAXIS_MIN, 0.0);
    registerProperty(P_ZAXIS_MAX, 0.0);

    ComboProperty gradient;
    gradient << "Grayscale" << "Hot" << "Cold" << "Night" << "Candy" << "Geography"
              << "Ion" << "Thermal" << "Polar" << "Spectrum" << "Jet" << "Hues";
    registerProperty(P_GRADIENT, gradient.getVariant());

    registerProperty(P_IS_LOGZ, true);
    registerProperty(P_IS_INTERPOLATED, true);
    registerProperty(P_XAXIS_TITLE, QString("x-axis"));
    registerProperty(P_YAXIS_TITLE, QString("y-axis"));
    registerProperty(P_AXES_UNITS, AngleProperty::Degrees());

}
