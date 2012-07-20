#ifndef TESTFITTINGMODULE_H_
#define TESTFITTINGMODULE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFittingModule.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jul 20, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

class TestFittingModule : public IFunctionalTest
{
public:
    TestFittingModule();
    virtual ~TestFittingModule();
    virtual void execute();

private:
    void initializeSample();
    void generateRealData(double noise_factor);
    OutputData<double> *mp_exact_data;
    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulated_data;
    ISample *mp_sample;
};


#endif /* TESTFITTINGMODULE_H_ */
