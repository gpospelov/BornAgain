// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFresnelCoeff.h 
//! @brief     Defines class TestFresnelCoeff.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTFRESNELCOEFF_H
#define TESTFRESNELCOEFF_H

#include "IFunctionalTest.h"
#include "OpticalFresnel.h"
#include "MultiLayer.h"
#include "OutputData.h"

//! Calculate Fresnel coefficients for several typical multilayer samples and produce validation plots

class TestFresnelCoeff : public IFunctionalTest
{
 public:
    TestFresnelCoeff();

    void execute();

 private:
    //! calculate Fresnel coefficients .vs. alpha_i for several standard samples
    void test_standard_samples();
    //! draw results of the test
    void draw_standard_samples();

    //! calculate Fresnel coefficients .vs. alpha_i for set of roughnesses
    void test_roughness_set();
    //! draw result of the test
    void draw_roughness_set();

    MultiLayer *mp_sample; //!< pointer to multilayer sample
    OutputData<OpticalFresnel::MultiLayerCoeff_t  > *mp_coeffs; //!< output data structure
};

#endif // TESTFRESNELCOEFF_H
