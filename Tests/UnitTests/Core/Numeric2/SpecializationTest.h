#include "google_test.h"
#include "Vectors3D.h"
#include "Complex.h"
#include "gtest/internal/gtest-param-util.h"
#include "HardParticles.h"

const complex_t I(0,1);
double eps_polyh = 7.5e-13;

using ::testing::Values;
using ::testing::internal::ParamGenerator;
using ::testing::Combine;

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


class SpecializationTest : public ::testing::Test
{
protected:
    SpecializationTest() : gen(qlist) {}
    ~SpecializationTest();

    void test_all(IFormFactorBorn* p0, IFormFactorBorn* p1, double eps=1e-12) {
        for (auto it : gen) {
            cvector_t qdir = std::get<0>(it);
            cvector_t qdev = std::get<1>(it);
            double    qmag = std::get<2>(it);
            complex_t qeps = std::get<3>(it);
            m_q = qmag * (qdir + qeps*qdev).unit();

            if (skip_q(1e-99, 5e2))
                continue;

            test_ff_eq(p0, p1, eps_polyh);
        }
    }

    void test_ff_eq(IFormFactorBorn* p0, IFormFactorBorn* p1, double eps=1e-12) {
        complex_t f0 = p0->evaluate_for_q(m_q);
        complex_t f1 = p1->evaluate_for_q(m_q);
        double avge = (std::abs(f0) + std::abs(f1))/2;
        //std::cout<<"q="<<q<<" -> "<<std::setprecision(16)<<" f0="<<f0<<", f1="<<f1<<"\n";
        EXPECT_NEAR( real(f0), real(f1), eps*avge );
        EXPECT_NEAR( imag(f0), imag(f1), eps*avge );
    }

    bool skip_q( double qmag_begin=1e-99, double qmag_end=1e99 ) {
        return m_q.mag()<=qmag_begin || m_q.mag()>=qmag_end;
    }

    cvector_t m_q;
    ParamGenerator<std::tuple<cvector_t, cvector_t, double, complex_t>> gen;
};

SpecializationTest::~SpecializationTest() = default;

TEST_F(SpecializationTest, Start)
{
    double L = 1.5, H = .24, alpha = .6;
    FormFactorAnisoPyramid p0(L, L, H, alpha);
    FormFactorPyramid p1(L, H, alpha);
    test_all(&p0, &p1, eps_polyh);
}
