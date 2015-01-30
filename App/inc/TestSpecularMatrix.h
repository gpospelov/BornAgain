// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestSpecularMatrix.h
//! @brief     Defines class TestSpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTSPECULARMATRIX_H_
#define TESTSPECULARMATRIX_H_

#include "IApplicationTest.h"
#include "SpecularMatrix.h"
#include "MultiLayer.h"
#include "OutputData.h"

//! Returns amplitudes for different wave components using the matrix formalism
//! for several typical multilayer samples and produce validation plots

class TestSpecularMatrix : public IApplicationTest
{
public:
    TestSpecularMatrix();

    void execute();

private:
    //! Returns amplitudes vs. alpha_i for several standard samples
    void test_standard_samples();
    //! draw results of the test
    void draw_standard_samples();

    //! Returns amplitudes vs. alpha_i for set of roughnesses
    void test_roughness_set();
    //! draw result of the test
    void draw_roughness_set();

    MultiLayer *mp_sample; //!< pointer to multilayer sample
    OutputData<SpecularMatrix::MultiLayerCoeff_t  >
        *mp_coeffs; //!< output data structure
};

#endif /* TESTSPECULARMATRIX_H_ */
