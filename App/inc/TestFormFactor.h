#ifndef TESTFORMFACTOR_H
#define TESTFORMFACTOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFormFactor.h
//! @brief  Definition of TestFormFactor class for formfactor validation
//! @author herk
//! @date   02.05.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"

class TestFormFactor : public IFunctionalTest
{
public:
    TestFormFactor();
    ~TestFormFactor();
    virtual void execute();
    void draw();

private:
    OutputData<double> *mp_intensity_output;
    FormFactorCylinder m_ff;
};


#endif // TESTFORMFACTOR_H
