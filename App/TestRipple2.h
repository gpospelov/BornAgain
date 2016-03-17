// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestRipple2.h
//! @brief     Defines class TestRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTRIPPLE2_H
#define TESTRIPPLE2_H


#include "IApplicationTest.h"
#include "ISampleBuilder.h"

class GISASSimulation;

class TestRipple2 : public IApplicationTest
{
public:
    TestRipple2();
    virtual ~TestRipple2() { }

    virtual void execute();
    void drawff ();

    //! Ripple2 sample builder (sample from PRB 85, 235415, 2012, fig.3)
    class TestSampleBuilder : public ISampleBuilder
    {
    public:
        TestSampleBuilder();
        virtual ISample *buildSample() const;
    protected:
        //! Registers some class members for later access via parameter pool
        virtual void init_parameters();
        double m_w; //width
        double m_h; //heigth
        double m_l; //length
        double m_d; //asymetry
        double m_interf_distance;
        double m_interf_width;
    };

private:

    //! Initializes simulation
    void initializeSimulation();


    //! plot IsGISAXS data and IsGISAXS fit results
    void save_results();
    void plot_results();


    GISASSimulation *mp_simulation;
    SampleBuilder_t mp_sample_builder;
};

#endif // TESTRIPPLE2_H


