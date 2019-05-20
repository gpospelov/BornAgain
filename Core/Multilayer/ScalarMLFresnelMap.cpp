// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarMLFresnelMap.cpp
//! @brief     Implements class ScalarMLFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ScalarMLFresnelMap.h"
#include "MultiLayer.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "SpecularMatrix.h"
#include "Vectors3D.h"

ScalarMLFresnelMap::ScalarMLFresnelMap()
{}

ScalarMLFresnelMap::~ScalarMLFresnelMap()
{}

std::unique_ptr<const ILayerRTCoefficients>
ScalarMLFresnelMap::getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index);
}

std::unique_ptr<const ILayerRTCoefficients>
ScalarMLFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index) const
{
    if (!m_use_cache) {
        auto coeffs = SpecularMatrix::execute(*mP_multilayer, kvec);
        return std::make_unique<const ScalarRTCoefficients>(coeffs[layer_index]);
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec);
    return std::make_unique<const ScalarRTCoefficients>(coef_vector[layer_index]);
}

const std::vector<ScalarRTCoefficients>&
ScalarMLFresnelMap::getCoefficientsFromCache(kvector_t kvec) const
{
    std::pair<double, double> k2_theta(kvec.mag2(), kvec.theta());
    auto it = m_hash_table.find(k2_theta);
    if (it == m_hash_table.end())
        it = m_hash_table.insert({k2_theta, SpecularMatrix::execute(*mP_multilayer, kvec)}).first;
    return it->second;
}
