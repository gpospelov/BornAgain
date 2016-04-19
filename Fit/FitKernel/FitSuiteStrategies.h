// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/FitSuiteStrategies.h
//! @brief     Declares class FitSuiteStrategies.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITESTRATEGIES_H
#define FITSUITESTRATEGIES_H

#include "SafePointerVector.h"
#include "IFitStrategy.h"

class FitKernel;

//! @class FitSuiteStrategies
//! @ingroup fitting_internal
//! @brief Collection of strategies to fit

class BA_CORE_API_ FitSuiteStrategies
{
public:
    FitSuiteStrategies();
    virtual ~FitSuiteStrategies();

    void init(FitKernel *fit_suite) { m_fit_kernel = fit_suite; }

    void addStrategy(IFitStrategy *strategy);

    void minimize();

    size_t getCurrentStrategyIndex() const { return m_current_strategy_index; }

    size_t size() const { return m_strategies.size(); }

    void clear();

    IFitStrategy *getCurrentStrategy();
    
private:
    SafePointerVector<IFitStrategy> m_strategies;
    FitKernel *m_fit_kernel;
    size_t m_current_strategy_index;
};

#endif // FITSUITESTRATEGIES_H
