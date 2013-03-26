#ifndef FITSUITEHELPER_H
#define FITSUITEHELPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuiteHelper.h
//! @brief  Collection of helper classes for fitting from App
//! @author Scientific Computing Group at FRM II
//! @date   08.10.2012


#include "FitSuitePrintObserver.h"
#include "FitSuiteDrawObserver.h"
#include "FitSuiteWriteTreeObserver.h"

class FitSuiteObserverFactory
{
public:
    typedef boost::shared_ptr<FitSuitePrintObserver > observer_print_t;
    typedef boost::shared_ptr<FitSuiteDrawObserver > observer_draw_t;
    typedef boost::shared_ptr<FitSuiteWriteTreeObserver > observer_tree_t;

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
