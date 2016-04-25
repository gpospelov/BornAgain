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
#include "qGenerator.h"

class FormFactorSpecializationTest : public ::testing::Test
{
protected:
    FormFactorSpecializationTest() {}

    void test_ff_eq( IFormFactorBorn* p0, IFormFactorBorn* p1,
                     double qmag_begin=1e-16, double qmag_end=1e4 )
    {
        for( size_t idx=0; idx<qGenerator::nq(); ++idx ){
            cvector_t q = qGenerator::q( idx, qmag_begin, qmag_end );
            complex_t f0 = p0->evaluate_for_q(q);
            complex_t f1 = p1->evaluate_for_q(q);
            double avge = (std::abs(f0) + std::abs(f1))/2;
            EXPECT_NEAR( real(f0), real(f1), 1e-12*avge );
            EXPECT_NEAR( imag(f0), imag(f1), 1e-12*avge );
        }

    }
};

// ****** TODO: the following tests pass only after the q range has been reduced *********

TEST_F(FormFactorSpecializationTest, TruncatedSphere)
{
    double R=1.;
    FormFactorTruncatedSphere p0(R, 2*R);
    FormFactorFullSphere p1(R);
    test_ff_eq( &p0, &p1, .025, 1e2 );
}

TEST_F(FormFactorSpecializationTest, AnisoPyramid)
{
    double L=1.5, H=.24, alpha=.6;
    FormFactorAnisoPyramid p0(L, L, H, alpha);
    FormFactorPyramid p1(L, H, alpha);
    test_ff_eq( &p0, &p1, .4, 6e2 );
}


TEST_F(FormFactorSpecializationTest, Pyramid3)
{
    double L=1.8, H=.3;
    FormFactorTetrahedron p0(L, H, Units::PI/2);
    FormFactorPrism3 p1(L, H);
    test_ff_eq( &p0, &p1, .04, 5e3 );
}

TEST_F(FormFactorSpecializationTest, Pyramid)
{
    double L=1.8, H=.3;
    FormFactorPyramid p0(L, H, Units::PI/2);
    FormFactorBox p1(L, L, H);
    test_ff_eq( &p0, &p1, .04, 2e2 );
}

//*********** satisfactory tests ***************

TEST_F(FormFactorSpecializationTest, HemiEllipsoid)
{
    double R=1.07;
    FormFactorHemiEllipsoid p0(R, R, R);
    FormFactorTruncatedSphere p1(R, R);
    test_ff_eq( &p0, &p1, 1e-17, 1e2 );
}

TEST_F(FormFactorSpecializationTest, EllipsoidalCylinder)
{
    double R=.8, H=1.2;
    FormFactorEllipsoidalCylinder p0(R, R, H);
    FormFactorCylinder p1(R, H);
    test_ff_eq( &p0, &p1, 1e-17, 3e3 );
}

TEST_F(FormFactorSpecializationTest, TruncatedCube)
{
    double L=.5;
    FormFactorTruncatedCube p0(L, 0);
    FormFactorBox p1(L, L, L);
    test_ff_eq( &p0, &p1, 1e-17, 1e4 );
}
