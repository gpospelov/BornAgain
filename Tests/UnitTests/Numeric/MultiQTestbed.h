#ifndef BORNAGAIN_TESTS_UNITTESTS_NUMERIC_MULTIQTESTBED_H
#define BORNAGAIN_TESTS_UNITTESTS_NUMERIC_MULTIQTESTBED_H

#include "Base/Vector/Vectors3D.h"
#include <functional>

//! Driver for FormFactorSpecializationTest and FormFactorSymmetryTest.

namespace formFactorTest {

//! Runs callback function "run_one_test(q)" for a huge number of different vectors q.
void run_test_for_many_q(std::function<void(cvector_t)> run_one_test, double qmag_min,
                         double qmag_max);

} // namespace formFactorTest

#endif // BORNAGAIN_TESTS_UNITTESTS_NUMERIC_MULTIQTESTBED_H
