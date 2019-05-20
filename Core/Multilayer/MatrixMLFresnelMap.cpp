// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixMLFresnelMap.cpp
//! @brief     Implements class MatrixMLFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MatrixMLFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MatrixRTCoefficients.h"
#include "MultiLayer.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"

namespace
{
std::vector<MatrixRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec);

const std::vector<MatrixRTCoefficients>&
getCoefficientsFromCache(kvector_t kvec, const MultiLayer& multilayer,
                         MatrixMLFresnelMap::CoefficientMap& hash_table);
} // namespace

MatrixMLFresnelMap::MatrixMLFresnelMap() = default;

MatrixMLFresnelMap::~MatrixMLFresnelMap() = default;

std::unique_ptr<const ILayerRTCoefficients>
MatrixMLFresnelMap::getOutCoefficients(const SimulationElement& sim_element,
                                       size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index, *mP_inverted_multilayer,
                           m_hash_table_out);
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixMLFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index) const
{
    return getCoefficients(kvec, layer_index, *mP_multilayer, m_hash_table_in);
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixMLFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index,
                                    const MultiLayer& multilayer, CoefficientMap& hash_table) const
{
    if (!m_use_cache) {
        auto coeffs = calculateCoefficients(multilayer, kvec);
        return std::make_unique<MatrixRTCoefficients>(coeffs[layer_index]);
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec, multilayer, hash_table);
    return std::make_unique<MatrixRTCoefficients>(coef_vector[layer_index]);
}

void MatrixMLFresnelMap::setMultilayer(const MultiLayer& multilayer)
{
    IMultiLayerFresnelMap::setMultilayer(multilayer);
    mP_inverted_multilayer.reset(multilayer.cloneInvertB());
}

namespace
{
std::vector<MatrixRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec)
{
    std::vector<MatrixRTCoefficients> coeffs;
    SpecularMagnetic::execute(multilayer, kvec, coeffs);
    return coeffs;
}

const std::vector<MatrixRTCoefficients>&
getCoefficientsFromCache(kvector_t kvec, const MultiLayer& multilayer,
                         MatrixMLFresnelMap::CoefficientMap& hash_table)
{
    auto it = hash_table.find(kvec);
    if (it == hash_table.end())
        it = hash_table.insert({kvec, calculateCoefficients(multilayer, kvec)}).first;
    return it->second;
}
} // namespace
