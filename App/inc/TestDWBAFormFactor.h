#ifndef TESTDWBAFORMFACTOR_H_
#define TESTDWBAFORMFACTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestDWBAFormFactor.h
//! @brief  Definition of TestDWBAFormFactor class for formfactor validation
//! @author herk
//! @date   02.05.2012


#include "IAlgorithm.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"
#include "DWBAFormFactor.h"

class TestDWBAFormFactor : public IAlgorithm
{
public:
    TestDWBAFormFactor();
    virtual ~TestDWBAFormFactor();
    virtual void execute();
    void draw();

private:
    OutputData<double> *mp_intensity_output;
    DWBAFormFactor m_dwba_ff;
};

complex_t reflection_fresnel(double alpha_i);
complex_t transmission_fresnel(double alpha_i);

#endif /* TESTDWBAFORMFACTOR_H_ */
