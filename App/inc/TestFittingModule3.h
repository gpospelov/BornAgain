#ifndef TESTFITTINGMODULE3_H
#define TESTFITTINGMODULE3_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFittingModule3.h
//! @brief  Definition of TestFittingModule3 class
//! @author Scientific Computing Group at FRM II
//! @date   Nov 23, 2012


#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "GISASExperiment.h"
#include "ISampleBuilder.h"
#include "SafePointerVector.h"
#include <vector>

class FitSuite;

//- -------------------------------------------------------------------
//! @class TestFittingModule3
//! @brief Simultaneous fit of several 1D scans (mixture of cylinders and prisms, 4 parameters)
//- -------------------------------------------------------------------
class TestFittingModule3 : public IFunctionalTest
{
public:
    typedef SafePointerVector<OutputData<double> >  DataScan_t;

    TestFittingModule3();
    virtual ~TestFittingModule3();
    virtual void execute();

private:
    void initializeSample();
    void initializeExperiment();
    void initializeRealData();

    GISASExperiment *m_experiment;
    ISample *m_sample;
    FitSuite *m_fitSuite;
    OutputData<double > *m_real_data;
    DataScan_t m_data_scans;
};
#endif // TESTFITTINGMODULE3_H
