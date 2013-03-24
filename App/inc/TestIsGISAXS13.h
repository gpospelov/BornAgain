// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestIsGISAXS13.h 
//! @brief     Defines class TestIsGISAXS13.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTISGISAXS13_H
#define TESTISGISAXS13_H


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
