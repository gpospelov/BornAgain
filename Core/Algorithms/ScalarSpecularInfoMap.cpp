// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/ScalarSpecularInfoMap.cpp
//! @brief     Implements class ScalarSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ScalarSpecularInfoMap.h"
#include "SpecularMatrix.h"


ScalarSpecularInfoMap::ScalarSpecularInfoMap(const MultiLayer *multilayer, int layer)
    : mp_multilayer(multilayer)
    , m_layer(layer)
{
}

ScalarSpecularInfoMap *ScalarSpecularInfoMap::clone() const
{
    return new ScalarSpecularInfoMap(mp_multilayer, m_layer);
}

//! \todo Can we avoid the code duplication in the two following functions ?

const ScalarRTCoefficients *ScalarSpecularInfoMap::getOutCoefficients(
        double alpha_f, double phi_f, double wavelength) const
{
    (void)phi_f;
    SpecularMatrix::MultiLayerCoeff_t coeffs;
    // phi has no effect on R,T, so just pass zero:
    kvector_t kvec = Geometry::vecOfLambdaAlphaPhi(wavelength, -alpha_f, 0.0);
    SpecularMatrix::execute(*mp_multilayer, kvec, coeffs);
    return new ScalarRTCoefficients(coeffs[m_layer]);
}

const ScalarRTCoefficients *ScalarSpecularInfoMap::getInCoefficients(
        double alpha_i, double phi_i, double wavelength) const
{
    (void)phi_i;
    SpecularMatrix::MultiLayerCoeff_t coeffs;
    // phi has no effect on R,T, so just pass zero:
    kvector_t kvec = Geometry::vecOfLambdaAlphaPhi(wavelength, alpha_i, 0.0);
    SpecularMatrix::execute(*mp_multilayer, kvec, coeffs);
    return new ScalarRTCoefficients(coeffs[m_layer]);
}
