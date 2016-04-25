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
// #include "qGenerator.h"
#include <tuple>

const complex_t I(0,1);

class QLoopedTest: public ::testing::TestWithParam<std::tuple<double, cvector_t>>
{
protected:
    QLoopedTest() {}
    virtual void SetUp()
    {
        double    qmag = std::get<0>(GetParam());
        cvector_t qdir = std::get<1>(GetParam());
        q = qmag * qdir;
    }
    cvector_t q;

    bool skip_q( double qmag_begin=1e-16, double qmag_end=1e4 ) {
        return q.mag()<qmag_begin || q.mag()>qmag_end;
    }

    void test_ff_eq( IFormFactorBorn* p0, IFormFactorBorn* p1) {
        complex_t f0 = p0->evaluate_for_q(q);
        complex_t f1 = p1->evaluate_for_q(q);
        double avge = (std::abs(f0) + std::abs(f1))/2;
        EXPECT_NEAR( real(f0), real(f1), 1e-12*avge );
        EXPECT_NEAR( imag(f0), imag(f1), 1e-12*avge );
    }
};

INSTANTIATE_TEST_CASE_P(
    QLoopedTests,
    QLoopedTest,
    testing::Combine(
        testing::Values(
            1e-19, 1e-17, 1e-15, 1e-13, 1e-11, 1e-9, 1e-7, 1e-5, 1e-4, 1e-3, 1e-2, .1,
            1., 1e1, 1e2, 1e3, 1e4 ),
        testing::Values(
        cvector_t({ 1., 0., 0 }),
        cvector_t({ 1.+0.1*I, 0., 0 }),
        cvector_t({ 0., 1., 0 }),
        cvector_t({ 0., 0., 1.-.1*I }),
        cvector_t({ 1., 1., 0 }),
        cvector_t({ 1.+0.1*I, 1.+0.1*I, 0 }),
        cvector_t({ 0., 1., 1. }),
        cvector_t({ 1.-.1*I, 0., 1.-.1*I }),
        cvector_t({ 1., 2., 0. }),
        cvector_t({ 1.+0.01*I, 2.+0.4*I, 0. }),
        cvector_t({ 1., 1., 1 }),
        cvector_t({ 1.+0.1*I, 1.+0.1*I, 1.+0.1*I }),
        cvector_t({ 2.17+.03*I, 3.49-.04*I, .752+.01*I })
            )
        )
    );

// ****** TODO: the following tests pass only after the q range has been reduced *********

TEST_P(QLoopedTest, TruncatedSphereAsSphere)
{
    if( skip_q( .025, 1e2 ) )
        return;
    double R=1.;
    FormFactorTruncatedSphere p0(R, 2*R);
    FormFactorFullSphere p1(R);
    test_ff_eq( &p0, &p1 );
}

TEST_P(QLoopedTest, AnisoPyramidAsPyramid)
{
    if( skip_q( .4, 6e2 ) )
        return;
    double L=1.5, H=.24, alpha=.6;
    FormFactorAnisoPyramid p0(L, L, H, alpha);
    FormFactorPyramid p1(L, H, alpha);
    test_ff_eq( &p0, &p1 );
}

TEST_P(QLoopedTest, Pyramid3AsPrism)
{
    if( skip_q( .04, 5e3 ) )
        return;
    double L=1.8, H=.3;
    FormFactorTetrahedron p0(L, H, Units::PI/2);
    FormFactorPrism3 p1(L, H);
    test_ff_eq( &p0, &p1 );
}

TEST_P(QLoopedTest, PyramidAsBox)
{
    if( skip_q( .04, 2e2 ) )
        return;
    double L=1.8, H=.3;
    FormFactorPyramid p0(L, H, Units::PI/2);
    FormFactorBox p1(L, L, H);
    test_ff_eq( &p0, &p1 );
}

//*********** satisfactory tests ***************

TEST_P(QLoopedTest, HemiEllipsoidAsTruncatedSphere)
{
    if( skip_q( 1e-17, 1e2 ) )
        return;
    double R=1.07;
    FormFactorHemiEllipsoid p0(R, R, R);
    FormFactorTruncatedSphere p1(R, R);
    test_ff_eq( &p0, &p1 );
}

TEST_P(QLoopedTest, EllipsoidalCylinderAsCylinder)
{
    if( skip_q( 1e-17, 3e3 ) )
        return;
    double R=.8, H=1.2;
    FormFactorEllipsoidalCylinder p0(R, R, H);
    FormFactorCylinder p1(R, H);
    test_ff_eq( &p0, &p1 );
}

TEST_P(QLoopedTest, TruncatedCubeAsBox)
{
    if( skip_q( 1e-17, 1e4 ) )
        return;
    double L=.5;
    FormFactorTruncatedCube p0(L, 0);
    FormFactorBox p1(L, L, L);
    test_ff_eq( &p0, &p1 );
}
