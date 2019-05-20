// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/KzComputation.h
//! @brief     Declares functions from KzComputation namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IKZCOMPUTATION_H
#define IKZCOMPUTATION_H

#include "Complex.h"
#include "ICloneable.h"
#include "Vectors3D.h"
#include <vector>

class MultiLayer;
class Slice;

//! Namespace containing functions for computing kz values for given multilayer and k (or kz) value
//! on the surface of the sample.
//! @ingroup simulation

namespace KzComputation
{
BA_CORE_API_ std::vector<complex_t> computeReducedKz(const MultiLayer& sample, kvector_t k);
BA_CORE_API_ std::vector<complex_t> computeKzFromSLDs(const MultiLayer& sample, double kz);
BA_CORE_API_ std::vector<complex_t> computeKzFromRefIndices(const MultiLayer& sample, kvector_t k);
BA_CORE_API_ std::vector<complex_t> computeReducedKz(std::vector<Slice>& slices, kvector_t k);
BA_CORE_API_ std::vector<complex_t> computeKzFromSLDs(std::vector<Slice>& slices, double kz);
BA_CORE_API_ std::vector<complex_t> computeKzFromRefIndices(std::vector<Slice>& slices, kvector_t k);
} // namespace KzComputation

#endif // IKZCOMPUTATION_H
