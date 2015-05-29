// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SpecularMatrix.h
//! @brief     Defines class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARMATRIX_H_
#define SPECULARMATRIX_H_

#include "Types.h"
#include "ISimulation.h"
#include "MultiLayer.h"
#include "ScalarRTCoefficients.h"
#include "EigenCore.h"


//! @class SpecularMatrix
//! @ingroup algorithms_internal
//! @brief Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer

class BA_CORE_API_ SpecularMatrix : public ISimulation
{
public:
    //! Layer coefficients describing refraction and reflection/transmission.
    typedef std::vector<ScalarRTCoefficients> MultiLayerCoeff_t;

    //! Computes refraction angle reflection/transmission coefficients
    //! for given multilayer and wavevector k
    static void execute(const MultiLayer& sample, const kvector_t& k, MultiLayerCoeff_t& coeff);

private:
   static Eigen::Matrix2cd calculatePMatrix(complex_t lower, complex_t upper);
};

#endif /* SPECULARMATRIX_H_ */
