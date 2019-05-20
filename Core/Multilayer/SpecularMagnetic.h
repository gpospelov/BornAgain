// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagnetic.h
//! @brief     Defines namespace SpecularMagnetic.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARMAGNETIC_H
#define SPECULARMAGNETIC_H

#include "MatrixRTCoefficients.h"
#include "Vectors3D.h"
#include <vector>

class MultiLayer;
class Slice;

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization.
//! @ingroup algorithms_internal

namespace SpecularMagnetic
{
//! Computes refraction angle reflection/transmission coefficients
//! for given multilayer and wavevector k
BA_CORE_API_ void Execute(const class MultiLayer& sample, const kvector_t k,
                          std::vector<MatrixRTCoefficients>& coeff);
}; // namespace SpecularMagnetic

#endif // SPECULARMAGNETIC_H
