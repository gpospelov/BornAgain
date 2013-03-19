// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Fitting/FitSuiteStrategies.h 
//! @brief     Defines class FitSuiteStrategies.
//
// ************************************************************************** //

#ifndef FITSUITESTRATEGIES_H
#define FITSUITESTRATEGIES_H

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
