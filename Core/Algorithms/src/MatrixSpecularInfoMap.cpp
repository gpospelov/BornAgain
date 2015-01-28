// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/ScalarSpecularInfoMap.cpp
//! @brief     Implements class ScalarSpecularInfoMap.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MatrixSpecularInfoMap.h"
#include "SpecularMagnetic.h"

#include <boost/scoped_ptr.hpp>


MatrixSpecularInfoMap::MatrixSpecularInfoMap(const MultiLayer *multilayer,
                                             int layer, double wavelength)
: m_layer(layer)
, m_wavelength(wavelength)
{
    mP_inverted_multilayer.reset(multilayer->cloneInvertB());
}

const MatrixRTCoefficients *MatrixSpecularInfoMap::getCoefficients(
        double alpha_f, double phi_f) const
{
    SpecularMagnetic specular_calculator;
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    kvector_t kvec;
    // phi has no effect on R,T, so just pass zero:
    kvec.setLambdaAlphaPhi(m_wavelength, alpha_f, phi_f);
    specular_calculator.execute(*mP_inverted_multilayer, -kvec, coeffs);
    return new MatrixRTCoefficients(coeffs[m_layer]);
}
