#ifndef TESTISGISAXS12_H
#define TESTISGISAXS12_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS12.h
//! @brief  Definition of TestIsGISAXS12 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   08.11.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "IsGISAXSData.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include <string>

class Experiment;
class FitSuite;

//- -------------------------------------------------------------------
//! @class TestIsGISAXS12
//! @brief Comparison with IsGISAXS ex-12: constrained fit example
//- -------------------------------------------------------------------
class TestIsGISAXS12 : public IFunctionalTest
{
public:
    TestIsGISAXS12();
    virtual ~TestIsGISAXS12();
    virtual void execute();

private:

    //! builds IsGISAXS ex-12 sample
    class TestSampleBuilder : public ISampleBuilder
    {
    public:
        TestSampleBuilder();
        virtual ~TestSampleBuilder(){}

        virtual ISample *buildSample() const;
    protected:
        //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
        virtual void init_parameters();
        double m_particle_probability1;
        double m_particle_radius1;
        double m_dispersion_radius1;
        double m_height_aspect_ratio1;
        double m_particle_probability2;
        double m_particle_radius2;
        double m_dispersion_radius2;
        double m_height_aspect_ratio2;
        double m_interf_distance;
        double m_interf_width;
    };

    //! initialize experiment
    void initialiseExperiment();

    //! run standard isgisaxs comparison
    void run_isgisaxs_comparison();

    //! plot IsGISAXS data and IsGISAXS fit results
    void plot_isgisaxs_fit_results();

    //! run isgisaxs ex-12 style fit
    void run_isgisaxs_fit();

    // -------------------------------
    // additional tests for debugging
    // -------------------------------

    //! run chi module test on isgisaxs data/result pair to check module numericaly
    void run_test_chimodule();
    //! run test minimizer to check whole chain
    void run_test_minimizer();
    //!  print axes
    void print_axes(IsGISAXSData::DataSet_t &data);

    Experiment *m_experiment;
    ISampleBuilder *m_sample_builder;
    FitSuite *m_fitSuite;
};


#endif // TESTISGISAXS12_H
