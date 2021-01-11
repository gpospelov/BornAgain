#include "Tests/UnitTests/Numeric/MultiQTestbed.h"
#include "Tests/GTestWrapper/google_test.h"

using ::testing::Combine;
using ::testing::Values;
using ::testing::internal::ParamGenerator;

namespace formFactorTest {

const auto qlist = testing::Combine(
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({0, 1, 1}),
                    cvector_t({1, 1, 1})),
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({1, 0, 1}),
                    cvector_t({1, 1, 1})),
    testing::Values(1e-19, 1e-17, 1e-15, 1e-12, 1e-9, 1e-6, 1e-3, .03, 1., 1e1, 1e2, 1e3, 1e4),
    testing::Values(0, -4e-16, +8e-16, -5e-11, 3e-7, -2e-3, .01, .1),
    testing::Values(-1e-15, +1e-14, -1e-11, 1e-7, -1e-3, .1, 1, sqrt(2), sqrt(3))
    );

void run_test_for_many_q(std::function<void(cvector_t)> run_one_test, double qmag_min,
                         double qmag_max)
{
    ParamGenerator<std::tuple<cvector_t, cvector_t, double, double, double>> gen = qlist;
    for (auto it : gen) {
        const cvector_t q_maindir = std::get<0>(it);
        const cvector_t q_sidedir = std::get<1>(it);
        const double qrealmag = std::get<2>(it);
        const double qimagrel = std::get<3>(it);
        const double qsidemag = std::get<4>(it);
        const complex_t qmag(qrealmag, qrealmag*qimagrel);
        if (std::abs(qmag) <= qmag_min || std::abs(qmag) >= qmag_max)
            continue;
        if (q_maindir == q_sidedir)
            continue;
        const cvector_t q = qmag * (q_maindir + qsidemag * q_sidedir).unit();

        run_one_test(q); // callback passed as argument
    }
}

} // namespace formFactorTest
