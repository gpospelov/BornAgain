// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/LayerSpecularInfo.cpp
//! @brief     Implements class LayerSpecularInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerSpecularInfo.h"

LayerSpecularInfo::LayerSpecularInfo()
{
}

LayerSpecularInfo* LayerSpecularInfo::clone() const
{
    LayerSpecularInfo *p_result = new LayerSpecularInfo;
    p_result->mP_out_coeff_map = this->mP_out_coeff_map;
    p_result->mP_in_coeffs = this->mP_in_coeffs;
    return p_result;
}

void LayerSpecularInfo::addOutCoefficients(
        ILayerRTCoefficients* rt_coefficients, double alpha_f, double phi_f)
{
    if (mP_out_coeff_map.get()) {
        mP_out_coeff_map->addCoefficients(rt_coefficients, alpha_f, phi_f);
    }
}

const ILayerRTCoefficients* LayerSpecularInfo::getOutCoefficients(
        double alpha_f, double phi_f) const
{
    return mP_out_coeff_map->getCoefficients(alpha_f, phi_f);
}
