// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterUtils.cpp
//! @brief     Implements namespace ParameterUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterUtils.h"
#include "ParameterDistribution.h"
#include "BornAgainNamespace.h"
#include "ParticleDistribution.h"
#include "ParameterPool.h"
#include "Particle.h"
#include "RealParameter.h"

namespace {
//! Returns list of all angle related parameters used in Core library.
std::vector<std::string> angleRelatedParameters() {
    std::vector<std::string> result {
        BornAgain::Inclination,
        BornAgain::Azimuth,
        BornAgain::Alpha,
        BornAgain::Beta,
        BornAgain::Gamma,
        BornAgain::Angle
    };
    return result;
}
}

bool ParameterUtils::isAngleRelated(const std::string& par_name)
{
    static std::vector<std::string> angleRelated = angleRelatedParameters();

    for (const auto& par : angleRelated) {
        if (par_name.find(par) != std::string::npos)
            return true;
    }

    return false;

}

std::string ParameterUtils::mainParUnits(const ParticleDistribution& distr)
{
    if (distr.particle() == nullptr)
        return BornAgain::UnitsNone;

    return poolParameterUnits(*distr.particle(),
                              distr.parameterDistribution().getMainParameterName());
}

std::string ParameterUtils::poolParameterUnits(const IParameterized& node,
                                               const std::string& parName)
{
    std::unique_ptr<ParameterPool> pool {node.createParameterTree()};
    return pool->getUniqueMatch(parName)->unit();
}
