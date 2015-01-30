// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestConvolution.h
//! @brief     Defines class TestConvolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTCONVOLUTION_H
#define TESTCONVOLUTION_H

#include "IApplicationTest.h"
#include "Convolve.h"
#include <string>
#include <vector>

//! Test Convolve class for instrumental effects studies.

class TestConvolution : public IApplicationTest
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
    typedef std::pair<std::string, MathFunctions::Convolve::EConvolutionMode> mode_pair_t;

    //! vector of pairs defined above
    std::vector<mode_pair_t> m_modes;

    //! number of peaks for convolution test function
    int m_npeaks;
};

#endif // TESTCONVOLUTION_H


