// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapHelper.cpp
//! @brief     Implements class ColorMapHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapHelper.h"
#include "item_constants.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"

namespace {
ColorMapHelper::gradient_map_t createGradientMap() {
    ColorMapHelper::gradient_map_t result;

    result[Constants::GRADIENT_GRAYSCALE] = QCPColorGradient::gpGrayscale;
    result[Constants::GRADIENT_HOT] = QCPColorGradient::gpHot;
    result[Constants::GRADIENT_COLD] = QCPColorGradient::gpCold;
    result[Constants::GRADIENT_NIGHT] = QCPColorGradient::gpNight;
    result[Constants::GRADIENT_CANDY] = QCPColorGradient::gpCandy;
    result[Constants::GRADIENT_GEOGRAPHY] = QCPColorGradient::gpGeography;
    result[Constants::GRADIENT_ION] = QCPColorGradient::gpIon;
    result[Constants::GRADIENT_THERMAL] = QCPColorGradient::gpThermal;
    result[Constants::GRADIENT_POLAR] = QCPColorGradient::gpPolar;
    result[Constants::GRADIENT_SPECTRUM] = QCPColorGradient::gpSpectrum;
    result[Constants::GRADIENT_JET] = QCPColorGradient::gpJet;
    result[Constants::GRADIENT_HUES] = QCPColorGradient::gpHues;

    return result;
}
}

ColorMapHelper::gradient_map_t ColorMapHelper::m_gradient_map = createGradientMap();



QCPColorGradient ColorMapHelper::getGradient(const QString &gradientName)
{
    auto it = m_gradient_map.find(gradientName);
    if(it == m_gradient_map.end()) {
        throw GUIHelpers::Error("ColorMapHelper::getGradient() -> Error. No such gradient" +
                                gradientName);
    }
    return QCPColorGradient(it.value());
}

QCPColorGradient ColorMapHelper::itemGradient(const IntensityDataItem *item)
{
    return getGradient(item->getGradient());
}
