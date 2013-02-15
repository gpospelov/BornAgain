#ifndef TESTISGISAXS13_H
#define TESTISGISAXS13_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS13.h
//! @brief  Definition of TestIsGISAXS13 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   18.01.2013


#include "IFunctionalTest.h"
#include "ISampleBuilder.h"

class Simulation;
class FitSuite;

//- -------------------------------------------------------------------
//! @class TestIsGISAXS
//! @brief Comparison with IsGISAXS ex-13: simulating annealing
//! (cylinders with size distribution and 1D paracrystal inderference function)
//- -------------------------------------------------------------------
class TestIsGISAXS13 : public IFunctionalTest
{
public:
    TestIsGISAXS13();
    virtual ~TestIsGISAXS13() { }

    virtual void execute();

private:
    //! initialize simulation
    void initializeSimulation();

    //! run standard isgisaxs comparison
    void run_isgisaxs_comparison();

    //! plot IsGISAXS data and IsGISAXS fit results
    void plot_isgisaxs_fit_results();

    //! run isgisaxs ex-13 style fit
    void run_isgisaxs_fit();

    Simulation *mp_simulation;
    ISampleBuilder *mp_sample_builder;
    FitSuite *mp_fitSuite;
};

#endif // TESTISGISAXS13_H
