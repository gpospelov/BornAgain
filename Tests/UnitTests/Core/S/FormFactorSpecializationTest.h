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

static complex_t I(0,1);

// different directions of q
static const int nqdir = 13;
static const cvector_t qdirs[nqdir] = {
    { 1., 0., 0 },
    { 1.+0.1*I, 0., 0 },
    { 0., 1., 0 },
    { 0., 0., 1.-.1*I },
    { 1., 1., 0 },
    { 1.+0.1*I, 1.+0.1*I, 0 },
    { 0., 1., 1. },
    { 1.-.1*I, 0., 1.-.1*I },
    { 1., 2., 0. },
    { 1.+0.01*I, 2.+0.4*I, 0. },
    { 1., 1., 1 },
    { 1.+0.1*I, 1.+0.1*I, 1.+0.1*I },
    { 2.17+.03*I, 3.49-.04*I, .752+.01*I }
};
// different magnitudes of q
static const int nqmag = 23;

class FormFactorSpecializationTest : public ::testing::Test
{
protected:
    FormFactorSpecializationTest() {}

    void test_ff_eq( IFormFactorBorn* p0, IFormFactorBorn* p1,
                     double qmag_beg=1e-16, double qmag_end=1e4 )
    {
        for( int idir=0; idir<nqdir; ++idir ){
            for( int jmag=0; jmag<nqmag; ++jmag ){
                double qmag =
                    pow( qmag_end, jmag/(nqmag-1.) ) *
                    pow( qmag_beg, (nqmag-1-jmag)/(nqmag-1.) );
                std::cout << "idir=" << idir << ", qmag=" << qmag << "\n";
                cvector_t q = qmag * qdirs[idir].unit();
                complex_t f0 = p0->evaluate_for_q(q);
                complex_t f1 = p1->evaluate_for_q(q);
                double avge = (std::abs(f0) + std::abs(f1))/2;
                EXPECT_NEAR( real(f0), real(f1), 1e-12*avge );
                EXPECT_NEAR( imag(f0), imag(f1), 1e-12*avge );
            }
        }

    }
};

TEST_F(FormFactorSpecializationTest, Sphere)
{
    double R=1.;
    FormFactorTruncatedSphere p0(R, 2*R);
    FormFactorFullSphere p1(R);
    test_ff_eq( &p0, &p1, .03, 1e2 );
}

TEST_F(FormFactorSpecializationTest, Cube)
{
    double L=.5;
    FormFactorTruncatedCube p0(L, 0);
    FormFactorBox p1(L, L, L);
    test_ff_eq( &p0, &p1, .3, 1e2 );
}

TEST_F(FormFactorSpecializationTest, Pyramid4)
{
    double L=1.5, H=.24, alpha=.6;
    FormFactorAnisoPyramid p0(L, L, H, alpha);
    FormFactorPyramid p1(L, H, alpha);
    test_ff_eq( &p0, &p1, .4, 6e2 );
}
