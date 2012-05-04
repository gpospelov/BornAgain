#ifndef TESTROUGHNESS_H
#define TESTROUGHNESS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestRoughness.h
//! @brief  Tests of roughness
//! @author Scientific Computing Group at FRM II
//! @date   02.05.2012

#include <vector>
#include "IAlgorithm.h"
#include "LayerRoughness.h"


class TestRoughness : public IAlgorithm
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
