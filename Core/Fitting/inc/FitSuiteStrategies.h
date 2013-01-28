#ifndef FITSUITESTRATEGIES_H
#define FITSUITESTRATEGIES_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuiteStrategies.h
//! @brief  Definition of FitSuiteStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   24.01.2013

#include "SafePointerVector.h"
#include "IFitSuiteStrategy.h"

class FitSuite;


//- -------------------------------------------------------------------
//! @class FitSuiteStrategies
//! @brief Collection of strategies to fit
//- -------------------------------------------------------------------
class FitSuiteStrategies
{
public:
    typedef SafePointerVector<IFitSuiteStrategy > strategies_t;

    FitSuiteStrategies();
    virtual ~FitSuiteStrategies();

    void init(FitSuite *fit_suite) { m_fit_suite = fit_suite; }

    void addStrategy(IFitSuiteStrategy *strategy);

    void minimize();

    size_t getNStrategy() const { return m_current_strategy_index; }

    void clear();
private:
    strategies_t m_strategies;
    FitSuite *m_fit_suite;
    size_t m_current_strategy_index;
};

#endif // FITSUITESTRATEGIES_H
