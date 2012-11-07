#ifndef TESTFOURIER_H_
#define TESTFOURIER_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFourier.h
//! @brief  Definition of TestFourier functional test class
//! @author Scientific Computing Group at FRM II
//! @date   Nov 6, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

class TestFourier : public IFunctionalTest
{
public:
    TestFourier();
    virtual ~TestFourier();
    virtual void execute();

private:
    void initializeSample();
    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;
};


#endif /* TESTFOURIER_H_ */
