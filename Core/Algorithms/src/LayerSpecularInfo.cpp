// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LayerSpecularInfo.cpp
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

LayerSpecularInfo::LayerSpecularInfo()
{
}

LayerSpecularInfo* LayerSpecularInfo::clone() const
{
    LayerSpecularInfo *p_result = new LayerSpecularInfo;
    p_result->mP_out_coeff_map.reset(this->mP_out_coeff_map->clone());
    p_result->mP_in_coeffs.reset(this->mP_in_coeffs->clone());
    return p_result;
}

void LayerSpecularInfo::addOutCoefficients(ISpecularInfoMap* rt_coefficient_map)
{
    if (mP_out_coeff_map.get() != rt_coefficient_map) {
        mP_out_coeff_map.reset(rt_coefficient_map);
    }
}

void LayerSpecularInfo::addInCoefficients(ILayerRTCoefficients *rt_coefficients) {
    if(mP_in_coeffs.get() != rt_coefficients) {
        mP_in_coeffs.reset(rt_coefficients);
    }
}

const ILayerRTCoefficients* LayerSpecularInfo::getOutCoefficients(
        double alpha_f, double phi_f) const
{
    return mP_out_coeff_map->getCoefficients(alpha_f, phi_f);
}
