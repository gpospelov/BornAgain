#ifndef TESTISGISAXS5_H
#define TESTISGISAXS5_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS5.h
//! @brief  Definition of TestIsGISAXS5 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   16.01.2013


#include "IFunctionalTest.h"
#include "ISampleBuilder.h"

class Simulation;
class FitSuite;

//- -------------------------------------------------------------------
//! @class TestIsGISAXS
//! @brief Comparison with IsGISAXS ex-5: LMA fitting of cylinders with
//! size distribution and 1D paracrystal inderference function.
//- -------------------------------------------------------------------
class TestIsGISAXS5 : public IFunctionalTest
{
public:
    TestIsGISAXS5();
    virtual ~TestIsGISAXS5() { }

    virtual void execute();

    //! IsGISAXS ex-5 sample builder
    class SampleBuilder : public ISampleBuilder
    {
    public:
        SampleBuilder();
        virtual ISample *buildSample() const;
    protected:
        //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
        virtual void init_parameters();
        double m_particle_radius;
        double m_dispersion_radius;
        double m_height_aspect_ratio;
        double m_interf_distance;
        double m_interf_width;
    };

private:

    //! initialize simulation
    void initializeSimulation();

    //! run standard isgisaxs comparison
    void run_isgisaxs_comparison();

    //! plot IsGISAXS data and IsGISAXS fit results
    void plot_isgisaxs_fit_results();

    //! run isgisaxs ex-5 style fit
    void run_isgisaxs_fit();

    Simulation *mp_simulation;
    ISampleBuilder *mp_sample_builder;
    FitSuite *mp_fitSuite;
};

#endif // TESTISGISAXS5_H
