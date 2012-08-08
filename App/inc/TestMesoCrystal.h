#ifndef TESTMESOCRYSTAL_H_
#define TESTMESOCRYSTAL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestMesoCrystal.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jul 13, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactors.h"
#include "DWBAFormFactor.h"
#include "ISample.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "MesoCrystal.h"


class TestMesoCrystal : public IFunctionalTest
{
public:
    TestMesoCrystal();
    virtual ~TestMesoCrystal();
    virtual void execute();

private:
    void initializeSample();
    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;
};

MesoCrystal *createMesoCrystal(double nanoparticle_radius, complex_t n_particle, const IFormFactor *p_meso_form_factor);


#endif /* TESTMESOCRYSTAL_H_ */
