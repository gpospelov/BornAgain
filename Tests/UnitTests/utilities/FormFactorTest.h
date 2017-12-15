#include "google_test.h"
#include "Vectors3D.h"
#include "Complex.h"
#include "gtest/internal/gtest-param-util.h"
#include "HardParticles.h"

using ::testing::Values;
using ::testing::internal::ParamGenerator;
using ::testing::Combine;

namespace TestData{

const complex_t I(0,1);

auto qlist = testing::Combine(
    testing::Values(
        cvector_t({ 1, 0, 0 }),
        cvector_t({ 0, 1, 0 }),
        cvector_t({ 0, 0, 1 }),
        cvector_t({ 1, 1, 0 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 1, 1 })
        ),
    testing::Values(
        cvector_t({ 1, 0, 0 }),
        cvector_t({ 0, 1, 0 }),
        cvector_t({ 0, 0, 1 }),
        cvector_t({ 1, 1, 0 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 0, 1 }),
        cvector_t({ 1, 1, 1 })
        ),
    testing::Values(
        1e-19, 1e-17, 1e-15, 1e-13, 1e-11, 1e-9, 1e-7, 1e-5, 1e-4, 1e-3, 1e-2, .1,
        1., 1e1, 1e2, 1e3, 1e4 ),
    testing::Values(
        -1e-15, +1e-14, -1e-13*I, +1e-12*I,
        -1e-11, +1e-10, -1e-9*I, +1e-8*I,
        -1e-7, +1e-6, -1e-5*I, +1e-4*I,
        -1e-3, +1e-2, -1e-1*I, +1e-1*I,
        .9, -.99, .999, -.9999 )
    );

}

class FormFactorTest : public ::testing::Test
{
protected:
    ~FormFactorTest();

    template<typename T>
    void test_all(double qmag1, double qmag2, T fun) {
        for (auto it : gen) {
            cvector_t qdir = std::get<0>(it);
            cvector_t qdev = std::get<1>(it);
            double    qmag = std::get<2>(it);
            complex_t qeps = std::get<3>(it);
            m_q = qmag * (qdir + qeps*qdev).unit();

            if (skip_q(qmag1, qmag2))
                continue;

            fun();
        }
    }

    bool skip_q( double qmag_begin=1e-99, double qmag_end=1e99 ) {
        return m_q.mag()<=qmag_begin || m_q.mag()>=qmag_end;
    }

    cvector_t m_q;
    static ParamGenerator<std::tuple<cvector_t, cvector_t, double, complex_t>> gen;
};

FormFactorTest::~FormFactorTest() = default;
ParamGenerator<std::tuple<cvector_t, cvector_t, double, complex_t>> FormFactorTest::gen = TestData::qlist;
