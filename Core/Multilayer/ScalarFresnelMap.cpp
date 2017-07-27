// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarFresnelMap.cpp
//! @brief     Implements class ScalarFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ScalarFresnelMap.h"
#include "MultiLayer.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "SpecularMatrix.h"

namespace {
std::vector<ScalarRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec);
}

ScalarFresnelMap::ScalarFresnelMap()
{}

ScalarFresnelMap::~ScalarFresnelMap()
{}

const ILayerRTCoefficients* ScalarFresnelMap::getOutCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index);
}

const ILayerRTCoefficients* ScalarFresnelMap::getInCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(sim_element.getKi(), layer_index);
}

const ScalarRTCoefficients* ScalarFresnelMap::getCoefficients(
        kvector_t kvec, size_t layer_index) const
{
    if (!m_use_cache) {
        auto coeffs { calculateCoefficients(*mP_multilayer, kvec) };
        return new ScalarRTCoefficients(coeffs[layer_index]);
    }
    ScalarRTCoefficients* result;
    std::pair<double, double> k2_theta(kvec.mag2(), kvec.theta());
    auto it = m_hash_table.find(k2_theta);
    if (it != m_hash_table.end())
        result = new ScalarRTCoefficients(it->second[layer_index]);
    else {
        auto coeffs { calculateCoefficients(*mP_multilayer, kvec) };
        result = new ScalarRTCoefficients(coeffs[layer_index]);
        m_hash_table[k2_theta] = std::move(coeffs);
    }
    return result;
}

namespace {
std::vector<ScalarRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec)
{
    std::vector<ScalarRTCoefficients> coeffs;
    SpecularMatrix::execute(multilayer, kvec, coeffs);
    return coeffs;
}
}
