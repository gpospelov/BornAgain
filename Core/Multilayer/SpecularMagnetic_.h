// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagnetic_.h
//! @brief     Defines class SpecularMagnetic_.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARMAGNETIC__H
#define SPECULARMAGNETIC__H

#include "MatrixRTCoefficients_.h"
#include "Vectors3D.h"
#include <vector>

class Slice;

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization.
//! @ingroup algorithms_internal
class BA_CORE_API_ SpecularMagnetic_
{
public:
    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and wavevector k
    static std::vector<MatrixRTCoefficients_> execute(const std::vector<Slice>& slices,
                                                      const kvector_t& k);

    //! Computes refraction angle reflection/transmission coefficients
    //! for given sliced multilayer and a set of kz projections corresponding to each slice
    static std::vector<MatrixRTCoefficients_> execute(const std::vector<Slice>& slices,
                                                      const std::vector<complex_t>& kzs);

    //! Computes frobenius matrices for multilayer solution
    static void calculateTR(MatrixRTCoefficients_& coeff);
    static void calculateZeroFieldTR(MatrixRTCoefficients_& coeff);

    static void setNoTransmission(MatrixRTCoefficients_& coeff);

    //! initializes reflectionless bottom boundary condition.
    static void nullifyBottomReflection(MatrixRTCoefficients_& coeff);

    //! Propagates boundary conditions from the bottom to the top of the layer stack.
    //! Used to compute boundary conditions from the bottom one (with nullified reflection)
    static void propagateBackwards(std::vector<MatrixRTCoefficients_>& coeff,
                                   const std::vector<Slice>& slices);

    //! finds linear coefficients for normalizing transmitted wave to unity.
    //! The left column of the returned matrix corresponds to the coefficients for pure spin-up
    //! wave, while the right column - to the coefficients for the spin-down one.
    static Eigen::Matrix2cd findNormalizationCoefficients(const MatrixRTCoefficients_& coeff);

    //! makes a linear combination of boundary conditions with using the given weights for each
    //! coefficient in the vector.
    static void propagateForwards(std::vector<MatrixRTCoefficients_>& coeff,
                                  const Eigen::Matrix2cd& weights);
};

#endif // SPECULARMAGNETIC__H
