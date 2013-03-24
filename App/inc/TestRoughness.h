// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestRoughness.h 
//! @brief     Defines class TestRoughness.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTROUGHNESS_H
#define TESTROUGHNESS_H

#include <vector>
#include "IFunctionalTest.h"
#include "LayerRoughness.h"

//! Draw profile of rough surface for different sets of roughness parameters.

//! Two models are used for profile calculation:
//! 1) matrix method 2) fast fourier transform using moving average
//!
class TestRoughness : public IFunctionalTest
{
public:
    TestRoughness();
    virtual ~TestRoughness(){}

    virtual void execute();

    /// draw profile of rough surface for different sets of roughness parameters
    void DrawProfile();

    /// calculate correlated z-coordinates of surface using matrix method
    void GetProfileXZ_MatrixMethod();

    /// calculate correlated z-coordinates of surface using fast fourier transform method
    void GetProfileXZ_FFTMethod();

    /// some tests of FFT
    void test_FFT();


private:
    LayerRoughness *m_roughness;    // pointer to roughness
    std::vector<double> m_vx;       // x-coordinates of grid along the surface
    std::vector<double> m_vzuncorr; // z coordiates of surface (heights) randomly generated with gaus
    std::vector<double> m_vzcorr;   // actial z coordinates of surface, correlated according correlation function of surface

    typedef void (TestRoughness::*TestMethod)();
    std::vector<TestMethod > m_TestMethods; // collection of class methods which will be used for correlated randoms
};

#endif // TESTROUGHNESS_H
