// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Reflections/LayerSpecularInfo.cpp
//! @brief     Implements class LayerSpecularInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerSpecularInfo.h"

LayerSpecularInfo* LayerSpecularInfo::clone() const
{
    LayerSpecularInfo *p_result = new LayerSpecularInfo;
    p_result->mP_coeff_map.reset(this->mP_coeff_map->clone());
    return p_result;
}

void LayerSpecularInfo::addRTCoefficients(ISpecularInfoMap* rt_coefficient_map)
{
    if (mP_coeff_map.get() != rt_coefficient_map) {
        mP_coeff_map.reset(rt_coefficient_map);
    }
}

const ILayerRTCoefficients* LayerSpecularInfo::getOutCoefficients(
        double alpha_f, double phi_f, double wavelength) const
{
    return mP_coeff_map->getOutCoefficients(alpha_f, phi_f, wavelength);
}

const ILayerRTCoefficients *LayerSpecularInfo::getInCoefficients(
        double alpha_i, double phi_i, double wavelength) const
{
    return mP_coeff_map->getInCoefficients(alpha_i, phi_i, wavelength);
}
