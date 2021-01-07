#include "Base/Math/Constants.h"
#include "Sample/HardParticle/HardParticles.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/Numeric/FormFactorTest.h"
#include "Sample/HardParticle/PolyhedralComponents.h" // for diagnostic

//! Check that form factors are invariant when q is transformed according to particle symmetry.

class FFSymmetryTest : public testing::Test {
private:
    using transform_t = std::function<cvector_t(const cvector_t&)>;

    void test_qq_eq(IBornFF* ff, cvector_t q, cvector_t p, double eps)
    {
        complex_t f0 = ff->evaluate_for_q(q);
#ifdef ALGORITHM_DIAGNOSTIC
        std::string msg0 = polyhedralDiagnosis.message();
#endif
        const complex_t f1 = ff->evaluate_for_q(p);
        const double avge = (std::abs(f0) + std::abs(f1)) / 2;
        const double precision = std::max(1e-16, eps*avge);
        EXPECT_NEAR(real(f0), real(f1), precision) << "q=" << q  << ", p=" << p
#ifdef ALGORITHM_DIAGNOSTIC
                                                    << "\n msg(q): " << msg0 << "\n"
                                                    << "\n msg(p): "
                                                    << polyhedralDiagnosis.message() << "\n"
#endif
            ;
        EXPECT_NEAR(imag(f0), imag(f1), precision) << "q=" << q  << ", p=" << p
#ifdef ALGORITHM_DIAGNOSTIC
                                                    << "\n msg(q): " << msg0 << "\n"
                                                    << "\n msg(p): "
                                                    << polyhedralDiagnosis.message() << "\n"
#endif
            ;
    }

protected:
    void run_test(IBornFF* ff, transform_t trafo, double eps, double qmag1, double qmag2)
    {
        formFactorTest::run_test_for_many_q([&](cvector_t q) { test_qq_eq(ff, q, trafo(q), eps); },
                                            qmag1, qmag2);
    }
};

//*********** polyhedra ***************

TEST_F(FFSymmetryTest, Prism3)
{
    FormFactorPrism3 p(.83, .45);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_TWOPI / 3); }, 1e-13, 1e-99,
        2e2);
}

TEST_F(FFSymmetryTest, Prism6)
{
    FormFactorPrism6 p(1.33, .42);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_PI / 3); }, 1e-13, 1e-99, 50);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(-M_TWOPI / 3); }, 1e-13,
        1e-99, 50);
}

TEST_F(FFSymmetryTest, Tetrahedron)
{
    FormFactorTetrahedron p(8.43, .25, .53);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_TWOPI / 3); }, 1e-11, 1e-99,
        2e2);
    // Linux: 3e-12, relaxed for Mac
}

TEST_F(FFSymmetryTest, Cone6_flat)
{
    // TODO for larger q, imag(ff) is nan
    FormFactorCone6 p(4.3, .09, .1);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(-M_PI / 3); }, 2e-12, 1e-99,
        50);
}

TEST_F(FFSymmetryTest, Cone6_steep)
{
    FormFactorCone6 p(.23, 3.5, .999 * M_PI / 2);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(-M_PI / 3); }, 1e-11, 1e-99,
        50);
}

//*********** spheroids ***************

TEST_F(FFSymmetryTest, HemiEllipsoid)
{
    FormFactorHemiEllipsoid p(.53, .78, 1.3);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return cvector_t(-q.x(), q.y(), q.z()); }, 1e-12,
        1e-99, 2e2);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return cvector_t(q.x(), -q.y(), q.z()); }, 1e-12,
        1e-99, 2e2);
}

TEST_F(FFSymmetryTest, TruncatedSphere)
{
    FormFactorTruncatedSphere p(.79, .34, 0);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(M_PI / 3.13698); }, 1e-12,
        1e-99, 2e2);
}

TEST_F(FFSymmetryTest, FullSpheroid)
{
    FormFactorFullSpheroid p(.73, .36);
    run_test(
        &p, [](const cvector_t& q) -> cvector_t { return q.rotatedZ(.123); }, 1e-12, 1e-99, 2e2);
}

// ****** TODO: tests that do not pass for the full q range *********
