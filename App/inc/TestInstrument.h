#ifndef TESTINSTRUMENT_H
#define TESTINSTRUMENT_H
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
class TestInstrument : public IFunctionalTest
{
public:
    TestInstrument();

    void execute();

    //! testing convolution in 1d
    void test_convolve1d();

    //! testing convolution in 2d
    void test_convolve2d();

private:
    typedef std::pair<std::string, MathFunctions::Convolve::Mode> mode_pair_t;
    std::vector<mode_pair_t> m_modes;
};

#endif // TESTINSTRUMENT_H
