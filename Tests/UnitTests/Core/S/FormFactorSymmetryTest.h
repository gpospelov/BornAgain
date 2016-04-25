// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactorSymmetryTest.h
//! @brief     Unit tests for symmetry of particle-shape form factors.
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
#include <tuple>

class FFSymmetryTest : public QLoopedTest
{
public:
    void test_qq_eq( IFormFactorBorn* p, cvector_t q0, cvector_t q1 ) {
        complex_t f0 = p->evaluate_for_q(q0);
        complex_t f1 = p->evaluate_for_q(q1);
        double avge = (std::abs(f0) + std::abs(f1))/2;
        EXPECT_NEAR( real(f0), real(f1), 1e-9*avge );
        EXPECT_NEAR( imag(f0), imag(f1), 1e-9*avge );
    }
    cvector_t qt;
};

INSTANTIATE_TEST_CASE_P(
    FFSymmetryTests,
    FFSymmetryTest,
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


TEST_P(FFSymmetryTest, Tetrahedron)
{
    if( skip_q( 2e-17, 2e2 ) )
        return;
    FormFactorTetrahedron p(8.43, .25, .53);
    test_qq_eq( &p, q, q.rotatedZ(Units::PI*2/3) );
}

//*********** satisfactory tests ***************

TEST_P(FFSymmetryTest, HemiEllipsoid)
{
    if( skip_q( 1e-99, 1e2 ) )
        return;
    FormFactorHemiEllipsoid p(.53, .78, 1.3);
    test_qq_eq( &p, q, cvector_t(-q.x(), q.y(), q.z()) );
    test_qq_eq( &p, q, cvector_t(q.x(), -q.y(), q.z()) );
}

TEST_P(FFSymmetryTest, Prism3)
{
    if( skip_q( 1e-99, 1e2 ) )
        return;
    FormFactorPrism3 p(.83, .45);
    test_qq_eq( &p, q, q.rotatedZ(Units::PI*2/3) );
}

