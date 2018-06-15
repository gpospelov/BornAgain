// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.cpp
//! @brief     Implements functor SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularComputationTerm.h"
#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "SpecularSimulationElement.h"

SpecularComputationTerm::SpecularComputationTerm(const IFresnelMap* p_fresnel_map)
    : mp_fresnel_map(p_fresnel_map)
{}

void SpecularComputationTerm::operator()(SpecularSimulationElement& elem) const
{
    if (elem.isCalculated()) {
        double intensity = std::norm(mp_fresnel_map->getInCoefficients(elem, 0)->getScalarR());
        elem.setIntensity(intensity);
    }
}
