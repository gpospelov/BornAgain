#ifndef TESTFITTINGMODULE1_H_
#define TESTFITTINGMODULE1_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFittingModule1.h
//! @brief  Definition of TestFittingModule class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 20, 2012


#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "GISASExperiment.h"
#include "ISampleBuilder.h"


class FitSuite;

//- -------------------------------------------------------------------
//! @class TestFittingModule1
//! @brief Testing of fitting module with simple samples
//- -------------------------------------------------------------------
class TestFittingModule1 : public IFunctionalTest
{
public:
    TestFittingModule1();
    virtual ~TestFittingModule1();
    virtual void execute();

private:
    //! initialize sample: layer + nanoparticles, 2 parameters
    void initializeSample1();
    //! initialize sample: layer + substrate + nanoparticles, 4 parameters
    void initializeSample2();

    void initializeExperiment();
    void initializeRealData();

    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulated_data;
    GISASExperiment *mp_experiment;
    ISample *mp_sample;
    FitSuite *m_fitSuite;
};


#endif /* TESTFITTINGMODULE1_H_ */
