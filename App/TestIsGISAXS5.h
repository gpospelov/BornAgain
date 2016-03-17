// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS5.h
//! @brief     Defines class TestIsGISAXS5.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTISGISAXS5_H
#define TESTISGISAXS5_H


#include "IApplicationTest.h"
#include "ISampleBuilder.h"

#include <GISASSimulation.h>

class Simulation;
class FitSuite;

//! IsGISAXS ex#5: LMA fit of cylinders with size distribution and radial paracrystal interference function.

class TestIsGISAXS5 : public IApplicationTest
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
        //! Registers some class members for later access via parameter pool
        virtual void init_parameters();
        double m_particle_radius;
        double m_dispersion_radius;
        double m_height_aspect_ratio;
        double m_interf_distance;
        double m_interf_width;
    };

private:

    //! Initializes simulation
    void initializeSimulation();

    //! run standard isgisaxs comparison
    void run_isgisaxs_comparison();

    //! plot IsGISAXS data and IsGISAXS fit results
    void plot_isgisaxs_fit_results();

    //! run isgisaxs ex-5 style fit
    void run_isgisaxs_fit();

    GISASSimulation *mp_simulation;
    SampleBuilder_t mp_sample_builder;
    FitSuite *mp_fitSuite;
};

#endif // TESTISGISAXS5_H


