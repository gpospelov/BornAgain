#include "FormFactorTest.h"

namespace TestData
{

const complex_t I(0, 1);

auto qlist = testing::Combine(
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({1, 0, 1}),
                    cvector_t({1, 1, 1})),
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({1, 0, 1}),
                    cvector_t({1, 1, 1})),
    testing::Values(1e-19, 1e-17, 1e-15, 1e-13, 1e-11, 1e-9, 1e-7, 1e-5, 1e-4, 1e-3, 1e-2, .1, 1.,
                    1e1, 1e2, 1e3, 1e4),
    testing::Values(-1e-15, +1e-14, -1e-13 * I, +1e-12 * I, -1e-11, +1e-10, -1e-9 * I, +1e-8 * I,
                    -1e-7, +1e-6, -1e-5 * I, +1e-4 * I, -1e-3, +1e-2, -1e-1 * I, +1e-1 * I, .9,
                    -.99, .999, -.9999));

} // namespace TestData

FormFactorTest::~FormFactorTest() = default;
ParamGenerator<std::tuple<cvector_t, cvector_t, double, complex_t>> FormFactorTest::gen =
    TestData::qlist;
