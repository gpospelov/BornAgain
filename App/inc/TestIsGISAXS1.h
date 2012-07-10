#ifndef TESTISGISAXS1_H_
#define TESTISGISAXS1_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS1.h
//! @brief  Definition of TestIsGISAXS1 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   Jun 28, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"


class TestIsGISAXS1 : public IFunctionalTest
{
public:
    TestIsGISAXS1();
    virtual ~TestIsGISAXS1();
    virtual void execute();

private:
    void initializeSample();
    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;
};


#endif /* TESTISGISAXS1_H_ */
