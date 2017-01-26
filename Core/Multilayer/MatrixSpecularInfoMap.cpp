// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixSpecularInfoMap.cpp
//! @brief     Implements class ScalarSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MatrixSpecularInfoMap.h"
#include "ILayerRTCoefficients.h"
#include "MatrixRTCoefficients.h"
#include "MultiLayer.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"

MatrixSpecularInfoMap::MatrixSpecularInfoMap(
        const MultiLayer* p_multilayer, const MultiLayer* p_inverted_multilayer,
        size_t layer_index)
    : mp_multilayer(p_multilayer)
    , mp_inverted_multilayer(p_inverted_multilayer)
    , m_layer_index(layer_index)
{}

MatrixSpecularInfoMap* MatrixSpecularInfoMap::clone() const
{
    return new MatrixSpecularInfoMap(mp_multilayer, mp_inverted_multilayer, m_layer_index);
}

const ILayerRTCoefficients* MatrixSpecularInfoMap::getOutCoefficients(
        const SimulationElement& sim_element) const
{
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    SpecularMagnetic::execute(*mp_inverted_multilayer, -sim_element.getMeanKf(), coeffs);
    return new MatrixRTCoefficients(coeffs[m_layer_index]);
}

const ILayerRTCoefficients* MatrixSpecularInfoMap::getInCoefficients(
        const SimulationElement& sim_element) const
{
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    SpecularMagnetic::execute(*mp_multilayer, sim_element.getKi(), coeffs);
    return new MatrixRTCoefficients(coeffs[m_layer_index]);
}
