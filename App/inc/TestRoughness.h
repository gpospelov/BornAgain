// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestRoughness.h
//! @brief     Defines class TestRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTROUGHNESS_H
#define TESTROUGHNESS_H

#include <vector>
#include "IApplicationTest.h"
#include "LayerRoughness.h"

//! Draw profile of rough surface for different sets of roughness parameters.

//! Two models are used for profile calculation:
//! 1) matrix method 2) fast Fourier transform using moving average
//!
class TestRoughness : public IApplicationTest
{
public:
    TestRoughness() : IApplicationTest("roughness"), m_roughness(0) {}
    virtual ~TestRoughness(){}

    virtual void execute();

    //! Draw profile of rough surface for different sets of roughness parameters
    void DrawProfile();

    //! Returns correlated z-coordinates of surface using matrix method.
    void GetProfileXZ_MatrixMethod();

    //! Returns correlated z-coordinates of surface using fast Fourier transform method.
    void GetProfileXZ_FFTMethod();

    //! Some tests of FFT.
    void test_FFT();

private:
    //! pointer to roughness
    LayerRoughness *m_roughness;
    //! x-coordinates of grid along the surface
    std::vector<double> m_vx;
    //! z coordinates of surface (heights) randomly generated with gaus
    std::vector<double> m_vzuncorr;
    //! actual z coordinates of surface, correlated according correlation function of surface [??]
    std::vector<double> m_vzcorr;

    typedef void (TestRoughness::*TestMethod)();
    //! collection of class methods which will be used for correlated randoms
    std::vector<TestMethod > m_TestMethods;
};

#endif // TESTROUGHNESS_H


