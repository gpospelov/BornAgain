#include "google_test.h"
#include "FormFactorTest.h"
#include "MathConstants.h"
#include <functional>

class FFSymmetryTest : public FormFactorTest
{
public:
    ~FFSymmetryTest();

    using transform_t = std::function<cvector_t(const cvector_t&)>;

    void run_test(IFormFactorBorn* p, transform_t fun, double eps, double qmag1, double qmag2)
    {
        test_all(qmag1, qmag2, [&](){test_qq_eq(p, fun, eps);});
    }

    void test_qq_eq( IFormFactorBorn* p, transform_t fun, double eps=1e-12 ) {
        complex_t f0 = p->evaluate_for_q(m_q);
        complex_t f1 = p->evaluate_for_q(fun(m_q));
        double avge = (std::abs(f0) + std::abs(f1))/2;
        EXPECT_NEAR( real(f0), real(f1), eps*avge );
        EXPECT_NEAR( imag(f0), imag(f1), eps*avge );
    }

};

FFSymmetryTest::~FFSymmetryTest() = default;

//*********** polyhedra ***************

TEST_F(FFSymmetryTest, Prism3)
{
    FormFactorPrism3 p(.83, .45);
    run_test(&p, [](const cvector_t& q)->cvector_t{return q.rotatedZ(M_TWOPI / 3);},
            1e-12, 1e-99, 2e2);
}

TEST_F(FFSymmetryTest, Prism6)
{
    FormFactorPrism6 p(1.33, .42);
    run_test(&p, [](const cvector_t& q)->cvector_t{return q.rotatedZ(M_PI / 3);},
            1e-12, 1e-99, 2e3);
    run_test(&p, [](const cvector_t& q)->cvector_t{return q.rotatedZ(-M_TWOPI / 3);},
            3.8e-12, 1e-99, 2e3);
}

TEST_F(FFSymmetryTest, Tetrahedron)
{
    FormFactorTetrahedron p(8.43, .25, .53);
    run_test(&p, [](const cvector_t& q)->cvector_t{return q.rotatedZ(M_TWOPI / 3);},
            6e-12, 1e-99, 2e2);
    // Linux: 3e-12, relaxed for Mac
}

TEST_F(FFSymmetryTest, Cone6_flat)
{
    // TODO for larger q, imag(ff) is nan
    FormFactorCone6 p(4.3, .09, .1);
    run_test(&p, [](const cvector_t& q)->cvector_t{return q.rotatedZ(-M_PI / 3);},
            3.8e-12, 1e-99, 2e2);
}

TEST_F(FFSymmetryTest, Cone6_steep)
{
    FormFactorCone6 p(.23, 3.5, .999 * M_PI / 2);
    run_test(&p, [](const cvector_t& q)->cvector_t{return q.rotatedZ(-M_PI / 3);},
            2.5e-12, 1e-99, 2e2);
}

//*********** spheroids ***************

TEST_F(FFSymmetryTest, HemiEllipsoid)
{
    FormFactorHemiEllipsoid p(.53, .78, 1.3);
    run_test(&p, [](const cvector_t& q)->cvector_t{return cvector_t(-q.x(), q.y(), q.z());},
            1e-12, 1e-99, 2e2);
    run_test(&p, [](const cvector_t& q)->cvector_t{return cvector_t(q.x(), -q.y(), q.z());},
            1e-12, 1e-99, 2e2);
}

TEST_F(FFSymmetryTest, TruncatedSphere)
{
    FormFactorTruncatedSphere p(.79, .34);
    run_test(&p, [](const cvector_t& q)->cvector_t{return q.rotatedZ(M_PI / 3.13698);},
            1e-10, 1e-99, 2e2);
}

// ****** TODO: tests that do not pass for the full q range *********
