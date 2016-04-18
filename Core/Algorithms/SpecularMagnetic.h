// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SpecularMagnetic.h
//! @brief     Defines class SpecularMagnetic.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARMAGNETIC_H_
#define SPECULARMAGNETIC_H_

#include "Types.h"
#include "ISimulation.h"
#include "MultiLayer.h"
#include "MatrixRTCoefficients.h"
#include "EigenCore.h"


//! @class SpecularMagnetic
//! @ingroup algorithms_internal
//! @brief Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization

class BA_CORE_API_ SpecularMagnetic : public ISimulation
{
public:
    //! Layer coefficients describing refraction and reflection/transmission.
    typedef std::vector<MatrixRTCoefficients> MultiLayerCoeff_t;

    //! Computes refraction angle reflection/transmission coefficients
    //! for given multilayer and wavevector k
    static void execute(const MultiLayer& sample, const kvector_t k,
           MultiLayerCoeff_t& coeff);

private:
    static void calculateEigenvalues(const MultiLayer& sample, const kvector_t k,
           MultiLayerCoeff_t& coeff);
    static void calculateTransferAndBoundary(const MultiLayer& sample,
           const kvector_t k, MultiLayerCoeff_t& coeff);
    static void setForNoTransmission(MultiLayerCoeff_t& coeff);
    static complex_t getImExponential(complex_t exponent);
};

#endif /* SPECULARMAGNETIC_H_ */
