#ifndef TESTISGISAXS9_H
#define TESTISGISAXS9_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS3.h
//! @brief  Definition of TestIsGISAXS9 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   02.07.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class TestIsGISAXS9
//! @brief Test of pyramid formfactor (correspond to IsGISAXS ex-9 example).
//- -------------------------------------------------------------------
class TestIsGISAXS9 : public IFunctionalTest
{
public:
    TestIsGISAXS9();
    virtual ~TestIsGISAXS9();
    virtual void execute();

private:
    void initializeSample();
    ISample *mp_sample;
    OutputData<double> *mp_intensity_output;
};


#endif // TESTISGISAXS9_H
