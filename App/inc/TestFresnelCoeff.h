// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFresnelCoeff.h
//! @brief  Definition of TestFresnelCoeff class for tests of Fresnel coeffs
//! @author Scientific Computing Group at FRM II
//! @date   02.05.2012
#ifndef TESTFRESNELCOEFF_H
#define TESTFRESNELCOEFF_H

#include "IAlgorithm.h"
#include "OpticalFresnel.h"
#include "MultiLayer.h"
#include "OutputData.h"


//- -------------------------------------------------------------------
//! @class TestFresnelCoeff
//! @brief Calculate Fresnel coefficients for several typical multilayer
//! samples and produce validation plots
//- -------------------------------------------------------------------
class TestFresnelCoeff : public IAlgorithm
{
public:
    TestFresnelCoeff();

    void execute();

    void draw();

private:
    MultiLayer *m_sample; //!< pointer to multilayer sample
    OutputData<OpticalFresnel::MultiLayerCoeff_t  > *m_coeffs; //!< output data structure
};


#endif // TESTFRESNELCOEFF_H
