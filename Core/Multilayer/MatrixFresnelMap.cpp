// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.cpp
//! @brief     Implements class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MatrixFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MatrixRTCoefficients.h"
#include "MultiLayer.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"

MatrixFresnelMap::MatrixFresnelMap(const MultiLayer* p_multilayer,
                                   const MultiLayer* p_inverted_multilayer)
    : mp_multilayer(p_multilayer)
    , mp_inverted_multilayer(p_inverted_multilayer)
{}

MatrixFresnelMap::~MatrixFresnelMap()
{}

const ILayerRTCoefficients* MatrixFresnelMap::getOutCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const
{
    MatrixRTCoefficients* result;
    kvector_t kvec = -sim_element.getMeanKf();
    auto it = m_hash_table_out.find(kvec);
    if (it != m_hash_table_out.end())
        result = new MatrixRTCoefficients(it->second[layer_index]);
    else {
        std::vector<MatrixRTCoefficients> coeffs;
        SpecularMagnetic::execute(*mp_inverted_multilayer, kvec, coeffs);
        result = new MatrixRTCoefficients(coeffs[layer_index]);
        m_hash_table_out[kvec] = std::move(coeffs);
    }
    return result;
}

const ILayerRTCoefficients* MatrixFresnelMap::getInCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const
{
    MatrixRTCoefficients* result;
    kvector_t kvec = sim_element.getKi();
    auto it = m_hash_table_in.find(kvec);
    if (it != m_hash_table_in.end())
        result = new MatrixRTCoefficients(it->second[layer_index]);
    else {
        std::vector<MatrixRTCoefficients> coeffs;
        SpecularMagnetic::execute(*mp_multilayer, kvec, coeffs);
        result = new MatrixRTCoefficients(coeffs[layer_index]);
        m_hash_table_in[kvec] = std::move(coeffs);
    }
    return result;
}
