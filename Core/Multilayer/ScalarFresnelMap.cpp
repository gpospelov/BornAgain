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

ScalarFresnelMap::ScalarFresnelMap(const MultiLayer* multilayer)
    : mp_multilayer(multilayer)
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
    ScalarRTCoefficients* result;
    auto it = m_hash_table.find(kvec);
    if (it != m_hash_table.end())
        result = new ScalarRTCoefficients(it->second[layer_index]);
    else {
        std::vector<ScalarRTCoefficients> coeffs;
        SpecularMatrix::execute(*mp_multilayer, kvec, coeffs);
        result = new ScalarRTCoefficients(coeffs[layer_index]);
        m_hash_table[kvec] = std::move(coeffs);
    }
    return result;
}
