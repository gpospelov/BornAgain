// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/IFitObserver.cpp
//! @brief     Implements class IFitObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFitObserver.h"
#include "FitSuite.h"
#include "FitSuiteStrategies.h"


IFitObserver::IFitObserver(int update_every_nth)
    : m_update_every_nth(update_every_nth)
    , m_current_strategy_index(-1)
    , m_strategy_has_changed(false)
{

}

void IFitObserver::notify(IObservable *subject)
{
    FitSuite *fit_suite = dynamic_cast<FitSuite *>(subject);
    if( !fit_suite ) throw NullPointerException("IFitObserver::update() -> Error! "
                                                "Can't access FitSuite");

    bool needs_update(false);

    if(fit_suite->getFitStrategies()->size() &&
            m_current_strategy_index != (int)fit_suite->getCurrentStrategyIndex()) {
        needs_update = true;
        m_current_strategy_index = fit_suite->getCurrentStrategyIndex();
        m_strategy_has_changed = true;
    } else {
        m_strategy_has_changed = false;
    }

    if( fit_suite->getNumberOfIterations() == 0 ) needs_update = true;  // first iteration
    if( fit_suite->isLastIteration() ) needs_update = true; // last iteration
    if( fit_suite->getNumberOfIterations() % m_update_every_nth == 0 ) needs_update = true; // every n'th iteration

    if(needs_update) update(fit_suite);
}

void IFitObserver::update(FitSuite *fit_suite)
{
    (void)fit_suite;
    throw NotImplementedException("IFitObserver::update(IObservable *subject) -> Error."
                                  "Not implemented.");
}
