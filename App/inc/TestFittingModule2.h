#ifndef TESTFITTINGMODULE2_H
#define TESTFITTINGMODULE2_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFittingModule2.h
//! @brief  Definition of TestFittingModule2 class
//! @author Scientific Computing Group at FRM II
//! @date   25.10.2012


#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "GISASExperiment.h"
#include "ISampleBuilder.h"
#include "FitSuiteStrategy.h"


class FitSuite;

//- -------------------------------------------------------------------
//! @class TestFittingModule2
//! @brief Testing of fitting module with 5 parameters sample using
//! sample builder, different fit strategies and chi2 modules
//- -------------------------------------------------------------------
class TestFittingModule2 : public IFunctionalTest
{
public:
    TestFittingModule2();
    virtual ~TestFittingModule2();
    virtual void execute();

    //! builds sample for fitter testing
    class TestSampleBuilder : public ISampleBuilder
    {
    public:
        TestSampleBuilder();
        virtual ~TestSampleBuilder(){}
        virtual ISample *buildSample() const;
    protected:
        virtual void init_parameters();
    private:
        double m_cylinder_height;
        double m_cylinder_radius;
        double m_prism3_half_side;
        double m_prism3_height;
        double m_cylinder_ratio;
    };

    //! basic fit example
    void fit_example_basics();

    //! fit example with chi2 module adjustment
    void fit_example_chimodule();

    //! fit example with strategies
    void fit_example_strategies();

private:
    void initializeExperiment();
    void initializeRealData();

    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulated_data;
    GISASExperiment *mp_experiment;
    ISampleBuilder *mp_sample_builder;
    FitSuite *m_fitSuite;
};


#endif // TESTFITTINGMODULE2_H
