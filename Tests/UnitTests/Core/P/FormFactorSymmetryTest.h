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

class FFSymmetryTest : public QLoopedTest
{
public:
    void test_qq_eq( IFormFactorBorn* p, cvector_t q0, cvector_t q1, double eps=1e-12 ) {
        complex_t f0 = p->evaluate_for_q(q0);
        complex_t f1 = p->evaluate_for_q(q1);
        double avge = (std::abs(f0) + std::abs(f1))/2;
        EXPECT_NEAR( real(f0), real(f1), eps*avge );
        EXPECT_NEAR( imag(f0), imag(f1), eps*avge );
    }
    cvector_t qt;
};

INSTANTIATE_TEST_CASE_P(
    FFSymmetryTests,
    FFSymmetryTest,
    qlist);

//*********** polyhedra ***************

TEST_P(FFSymmetryTest, Prism3)
{
    if( skip_q( 1e-99, 2e2 ) )
        return;
    FormFactorPrism3 p(.83, .45);
    test_qq_eq( &p, q, q.rotatedZ(Units::PI2/3) );
}

TEST_P(FFSymmetryTest, Prism6)
{
    if( skip_q( 1e-99, 2e3 ) )
        return;
    FormFactorPrism6 p(1.33, .42);
    test_qq_eq( &p, q, q.rotatedZ( Units::PI/3),  1e-12 );
    test_qq_eq( &p, q, q.rotatedZ(-Units::PI2/3), 3.8e-12 );
}

TEST_P(FFSymmetryTest, Tetrahedron)
{
    if( skip_q( 1e-99, 2e2 ) )
        return;
    FormFactorTetrahedron p(8.43, .25, .53);
    test_qq_eq( &p, q, q.rotatedZ(Units::PI2/3), 3e-12 );
}

TEST_P(FFSymmetryTest, Cone6_flat)
{
    if( skip_q( 1e-99, 2e2) ) // TODO for larger q, imag(ff) is nan
        return;
    FormFactorCone6 p(4.3, .09, .1);
    test_qq_eq( &p, q, q.rotatedZ(-Units::PI/3), 3.8e-12 );
}

TEST_P(FFSymmetryTest, Cone6_steep)
{
    if( skip_q( 1e-99, 2e2) ) // TODO for larger q, imag(ff) is nan
        return;
    FormFactorCone6 p(.23, 3.5, .999*Units::PI/2);
    test_qq_eq( &p, q, q.rotatedZ(-Units::PI/3), 2.5e-12 );
}

//*********** spheroids ***************

TEST_P(FFSymmetryTest, HemiEllipsoid)
{
    if( skip_q( 1e-99, 2e2 ) )
        return;
    FormFactorHemiEllipsoid p(.53, .78, 1.3);
    test_qq_eq( &p, q, cvector_t(-q.x(), q.y(), q.z()) );
    test_qq_eq( &p, q, cvector_t(q.x(), -q.y(), q.z()) );
}

TEST_P(FFSymmetryTest, TruncatedSphere)
{
    if( skip_q( 1e-99, 2e2 ) )
        return;
    FormFactorTruncatedSphere p(.79, .34);
    test_qq_eq( &p, q, q.rotatedZ(Units::PI/3.13698), 1e-10 );
}

// ****** TODO: tests that do not pass for the full q range *********
