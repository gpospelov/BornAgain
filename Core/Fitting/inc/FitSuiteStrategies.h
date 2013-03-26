// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/inc/FitSuiteStrategies.h
//! @brief     Defines class FitSuiteStrategies.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FITSUITESTRATEGIES_H
#define FITSUITESTRATEGIES_H

#include "SafePointerVector.h"
#include "IFitSuiteStrategy.h"

class FitSuite;

//! Collection of strategies to fit

class FitSuiteStrategies
{
 public:
    typedef SafePointerVector<IFitSuiteStrategy > strategies_t;
    typedef strategies_t::iterator iterator;

    FitSuiteStrategies();
    virtual ~FitSuiteStrategies();

    void init(FitSuite *fit_suite) { m_fit_suite = fit_suite; }

    void addStrategy(IFitSuiteStrategy *strategy);

    void minimize();

    size_t getNStrategy() const { return m_current_strategy_index; }

    iterator begin() { return m_strategies.begin(); }
    iterator end() { return m_strategies.end(); }

    void clear();
 private:
    strategies_t m_strategies;
    FitSuite *m_fit_suite;
    size_t m_current_strategy_index;
};

#endif // FITSUITESTRATEGIES_H
