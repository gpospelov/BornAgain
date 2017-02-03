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

const ILayerRTCoefficients* MatrixFresnelMap::getOutCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const
{
    std::vector<MatrixRTCoefficients> coeffs;
    SpecularMagnetic::execute(*mp_inverted_multilayer, -sim_element.getMeanKf(), coeffs);
    return new MatrixRTCoefficients(coeffs[layer_index]);
}

const ILayerRTCoefficients* MatrixFresnelMap::getInCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const
{
    std::vector<MatrixRTCoefficients> coeffs;
    SpecularMagnetic::execute(*mp_multilayer, sim_element.getKi(), coeffs);
    return new MatrixRTCoefficients(coeffs[layer_index]);
}
