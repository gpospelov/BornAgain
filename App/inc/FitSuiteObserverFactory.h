// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/FitSuiteObserverFactory.h
//! @brief     Defines classes FitSuiteObserverFactory, FitSuiteObserverPrint, FitSuiteObserverDraw, FitSuiteObserverWriteTree
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEOBSERVERFACTORY_H
#define FITSUITEOBSERVERFACTORY_H

#include "FitSuitePrintObserver.h"
#include "FitSuiteDrawObserver.h"
#include "FitSuiteWriteTreeObserver.h"
#include <boost/shared_ptr.hpp>

//! factory to create observers for FitSuite
class FitSuiteObserverFactory
{
 public:
    typedef boost::shared_ptr<FitSuitePrintObserver> observer_print_t;
    typedef boost::shared_ptr<FitSuiteDrawObserver> observer_draw_t;
    typedef boost::shared_ptr<FitSuiteWriteTreeObserver> observer_tree_t;

    static observer_print_t createPrintObserver(int run_every_nth=20) {
        return observer_print_t( new FitSuitePrintObserver(run_every_nth) );
    }

    static observer_draw_t createDrawObserver(int run_every_nth=20) {
        return observer_draw_t( new FitSuiteDrawObserver(run_every_nth) );
    }

    static observer_tree_t createTreeObserver() {
        return observer_tree_t( new FitSuiteWriteTreeObserver() );
    }
};

#endif // FITSUITEHELPER_H


