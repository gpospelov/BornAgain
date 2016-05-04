// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactorSpecializationTest.h
//! @brief     Unit tests for special cases of particle-shape form factors.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Units.h"
#include "BornAgainNamespace.h"
#include "IFormFactorBorn.h"
#include "ParticleShapes.h"
#include "qLoopedTest.h"

class FFSpecializationTest : public QLoopedTest
{
public:
    void test_ff_eq( IFormFactorBorn* p0, IFormFactorBorn* p1, double eps=1e-12) {
        complex_t f0 = p0->evaluate_for_q(q);
        complex_t f1 = p1->evaluate_for_q(q);
        double avge = (std::abs(f0) + std::abs(f1))/2;
        //std::cout<<"q="<<q<<" -> "<<std::setprecision(16)<<" f0="<<f0<<", f1="<<f1<<"\n";
        EXPECT_NEAR( real(f0), real(f1), eps*avge );
        EXPECT_NEAR( imag(f0), imag(f1), eps*avge );
    }
};

INSTANTIATE_TEST_CASE_P(
    FFSpecializationTests,
    FFSpecializationTest,
    qlist);

TEST_P(FFSpecializationTest, HemiEllipsoidAsTruncatedSphere)
{
    if( skip_q( 1e-99, 5e2 ) )
        return;
    double R=1.07;
    FormFactorHemiEllipsoid p0(R, R, R);
    FormFactorTruncatedSphere p1(R, R);
    test_ff_eq( &p0, &p1, 1e-10 );
}

TEST_P(FFSpecializationTest, EllipsoidalCylinderAsCylinder)
{
    if( skip_q( 1e-99, 5e3 ) )
        return;
    double R=.8, H=1.2;
    FormFactorEllipsoidalCylinder p0(R, R, H);
    FormFactorCylinder p1(R, H);
    test_ff_eq( &p0, &p1, 1e-11 );
}

TEST_P(FFSpecializationTest, TruncatedCubeAsBox)
{
    if( skip_q( 1e-99, 5e3 ) )
        return;
    double L=.5;
    FormFactorTruncatedCube p0(L, 0);
    FormFactorBox p1(L, L, L);
    test_ff_eq( &p0, &p1, 1e-11 );
}

TEST_P(FFSpecializationTest, AnisoPyramidAsPyramid)
{
    if( skip_q( 1e-99, 5e3 ) )
        return;
    double L=1.5, H=.24, alpha=.6;
    FormFactorAnisoPyramid p0(L, L, H, alpha);
    FormFactorPyramid p1(L, H, alpha);
    test_ff_eq( &p0, &p1, 1e-9 );
}

TEST_P(FFSpecializationTest, TruncatedSphereAsSphere)
{
    if( skip_q( .02, 5e1 ) ) // WAITING #1416 improve/replace numeric integration
        return;
    double R=1.;
    FormFactorTruncatedSphere p0(R, 2*R);
    FormFactorFullSphere p1(R);
    test_ff_eq( &p0, &p1 );
}

TEST_P(FFSpecializationTest, Pyramid3AsPrism)
{
    if( skip_q( 1e-99, 5e3 ) )
        return;
    double L=1.8, H=.3;
    FormFactorTetrahedron p0(L, H, Units::PI/2);
    FormFactorPrism3 p1(L, H);
    test_ff_eq( &p0, &p1, 2e-9 );
}

TEST_P(FFSpecializationTest, PyramidAsBox)
{
    if( skip_q( 1e-99, 5e2 ) )
        return;
    double L=1.8, H=.3;
    FormFactorPyramid p0(L, H, Units::PI/2);
    FormFactorBox p1(L, L, H);
    test_ff_eq( &p0, &p1, 5e-10 );
}

TEST_P(FFSpecializationTest, Cone6AsPrism)
{
    if( skip_q( 1e-99, 5e2 ) )
        return;
    double L=.8, H=1.13;
    FormFactorCone6 p0(L, H, Units::PI/2);
    FormFactorPrism6 p1(L, H);
    test_ff_eq( &p0, &p1, 2e-10 );
}
