#include "Complex.h"
#include "HardParticles.h"
#include "Vectors3D.h"
#include "google_test.h"
#include "gtest/internal/gtest-param-util.h"

using ::testing::Combine;
using ::testing::Values;
using ::testing::internal::ParamGenerator;

class FormFactorTest : public ::testing::Test
{
protected:
    ~FormFactorTest();

    template <typename T> void test_all(double qmag1, double qmag2, T fun)
    {
        for (auto it : gen) {
            cvector_t qdir = std::get<0>(it);
            cvector_t qdev = std::get<1>(it);
            double qmag = std::get<2>(it);
            complex_t qeps = std::get<3>(it);
            m_q = qmag * (qdir + qeps * qdev).unit();

            if (skip_q(qmag1, qmag2))
                continue;

            fun();
        }
    }

    bool skip_q(double qmag_begin = 1e-99, double qmag_end = 1e99)
    {
        return m_q.mag() <= qmag_begin || m_q.mag() >= qmag_end;
    }

    cvector_t m_q;
    static ParamGenerator<std::tuple<cvector_t, cvector_t, double, complex_t>> gen;
};
