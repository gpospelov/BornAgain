#ifndef TESTMESOCRYSTAL1_H_
#define TESTMESOCRYSTAL1_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestMesoCrystal1.h
//! @brief  Definition of TestMesoCrystal1 class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 13, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactors.h"
#include "FormFactorDWBA.h"
#include "ISample.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "MesoCrystal.h"
#include "Lattice.h"


//- -------------------------------------------------------------------
//! @class TestMesoCrystal1
//! @brief Simulation of 3D ordered particle assemblies
//- -------------------------------------------------------------------
class TestMesoCrystal1 : public IFunctionalTest
{
public:
    TestMesoCrystal1();
    virtual ~TestMesoCrystal1();
    virtual void execute();

private:
    void initializeSample();
    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;
};

MesoCrystal *createMesoCrystal(double particle_radius, complex_t n_particle, const IFormFactor *p_meso_form_factor);
const Lattice *createLattice(double stacking_radius);

#endif /* TESTMESOCRYSTAL1_H_ */
