// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputation.cpp
//! @brief     Implements class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SpecularComputation.h"
#include "SimulationElement.h"
#include "ILayerSpecularInfo.h"
#include "ILayerRTCoefficients.h"
#include "MultiLayer.h"

SpecularComputation::SpecularComputation(const MultiLayer* p_multi_layer)
    : IComputationTerm(p_multi_layer)
{}

bool SpecularComputation::eval(
    const SimulationOptions&, ProgressHandler*, bool,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it) const
{
    if (mp_multilayer->requiresMatrixRTCoefficients())
        return false;

    for (auto it = begin_it; it != end_it; ++it) {
        if (it->containsSpecularWavevector()) {
            complex_t R = (*mp_specular_info_map)[0]->getInCoefficients(*it)->getScalarR();
            double sin_alpha_i = std::abs(std::sin(it->getAlphaI()));
            if (sin_alpha_i==0.0)
                sin_alpha_i = 1.0;
            double solid_angle = it->getSolidAngle();
            if (solid_angle<=0.0)
                continue;
            double intensity = std::norm(R)*sin_alpha_i/solid_angle;
            it->setIntensity(intensity);
        } else {
            it->setIntensity(0.0);
        }
    }
    return true;
}
