#include "Base/Math/Constants.h"
#include "Sample/HardParticle/HardParticles.h"
#include "Sample/HardParticle/PolyhedralComponents.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>

//! Ad-hoc test of tetrahedron form factor.
//!
//! Used while preparing polyhedral form factor manuscript for publication - JWu, dec 2020.
//!
//! To reactivate this code, just move in to ../UnitTest/Numeric/.

class AdHoc : public ::testing::Test {
};

void run(const IBornFF& ff, const cvector_t& q, const cvector_t& p)
{
    const complex_t ffq = ff.evaluate_for_q(q);
    std::cout << std::setprecision(16) << q << " -> " << ffq << "\n";
#ifdef ALGORITHM_DIAGNOSTIC
    std::cout << polyhedralDiagnosis.message() << "\n";
    polyhedralDiagnosis.reset();
#endif
    const complex_t ffp = ff.evaluate_for_q(p);
    std::cout << std::setprecision(16) << p << " -> " << ffp << "\n";
#ifdef ALGORITHM_DIAGNOSTIC
    std::cout << polyhedralDiagnosis.message() << "\n";
    polyhedralDiagnosis.reset();
#endif
    std::cout << "diff(ff)=" << ffq - ffp << "\n\n";
}

TEST_F(AdHoc, FF)
{
    FormFactorTetrahedron ff(8.43, .25, .53);
    cvector_t q, p;
    q = {{.03, -4e-16}, {-3e-17, 0}, {0, 0}};
    run(ff, q, q.rotatedZ(M_TWOPI / 3));

    q = {{.03, 0}, {-3e-17, 0}, {0, 0}};
    run(ff, q, q.rotatedZ(M_TWOPI / 3));

    EXPECT_EQ(0, 0);
}
