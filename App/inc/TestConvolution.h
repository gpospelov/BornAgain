#ifndef TESTCONVOLUTION_H
#define TESTCONVOLUTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestConvolution.h
//! @brief  Definition of TestConvolution class for testing of Convolve class
//! @author Scientific Computing Group at FRM II
//! @date   02.05.2012

#include "IFunctionalTest.h"
#include "Convolve.h"
#include <string>
#include <vector>


//- -------------------------------------------------------------------
//! @class TestConvolution
//! @brief Testing Convolve class for instrumental effects studies
//- -------------------------------------------------------------------
class TestConvolution : public IFunctionalTest
{
public:
    TestConvolution();

    void execute();

    //! testing convolution in 1d
    void test_convolve1d();

    //! testing convolution in 2d
    void test_convolve2d();

private:
    //! test function with many gaus'es on top of flat background for convolution studies
    double fpeaks(double *x, double *par);

    //! typedef of pair for the description of convolution mode
    typedef std::pair<std::string, MathFunctions::Convolve::Mode> mode_pair_t;

    //! vector of pairs defined above
    std::vector<mode_pair_t> m_modes;

    //! number of peaks for convolution test function
    int m_npeaks;
};

#endif // TESTCONVOLUTION_H
