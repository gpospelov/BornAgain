#ifndef IKZCOMPUTATION_H
#define IKZCOMPUTATION_H

#include "Complex.h"
#include "ICloneable.h"
#include "Vectors3D.h"
#include <vector>

class MultiLayer;

namespace KzComputation
{
BA_CORE_API_ std::vector<complex_t> computeReducedKz(const MultiLayer& sample, kvector_t k);
BA_CORE_API_ std::vector<complex_t> computeKzFromSLDs(const MultiLayer& sample, double kz);
BA_CORE_API_ std::vector<complex_t> computeKzFromRefIndeces(const MultiLayer& sample, kvector_t k);
} // namespace KzComputation

#endif // IKZCOMPUTATION_H
