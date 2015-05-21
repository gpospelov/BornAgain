// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS12.h
//! @brief     Defines class TestIsGISAXS12.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTISGISAXS12_H
#define TESTISGISAXS12_H

#include "IApplicationTest.h"
#include "OutputData.h"
#include "IsGISAXSData.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "GISASSimulation.h"
#include <string>

class Simulation;
class FitSuite;

//! IsGISAXS ex#12: Constrained fit.

class TestIsGISAXS12 : public IApplicationTest
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
        //! Registers some class members for later access via parameter pool
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

    //! Initializes simulation
    void initializeSimulation();

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
    void print_axes(IsGISAXSData::DataSet_t& data);

    GISASSimulation *m_simulation;
    SampleBuilder_t m_sample_builder;
    FitSuite *m_fitSuite;
};

#endif // TESTISGISAXS12_H


