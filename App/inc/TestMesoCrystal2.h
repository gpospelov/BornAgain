#ifndef TESTMESOCRYSTAL2_H
#define TESTMESOCRYSTAL2_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestMesoCrystal2.h
//! @brief  Definition of Layer class
//! @author Scientific Computing Group at FRM II
//! @date   27.09.2012

#include "IFunctionalTest.h"
#include "Types.h"
#include "OutputData.h"

class MesoCrystal;
class IFormFactor;
class Lattice;
class ISample;

//- -------------------------------------------------------------------
//! @class TestMesoCrystal2
//! @brief Simulation of 3D ordered particle assemblies
//- -------------------------------------------------------------------
class TestMesoCrystal2 : public IFunctionalTest
{
public:
    TestMesoCrystal2();
    virtual ~TestMesoCrystal2();

    virtual void execute();

    void initializeSample();
    MesoCrystal* createMesoCrystal(double stacking_radius, complex_t n_particle, const IFormFactor* p_meso_form_factor);
    const Lattice *createLattice(double stacking_radius);

    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;

};

#endif // TESTMESOCRYSTAL2_H
