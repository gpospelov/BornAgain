// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/IFitObserver.cpp
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


IFitObserver::IFitObserver(int update_every_nth)
    : m_update_every_nth(update_every_nth)
    , m_current_strategy_index(-1)
{

}

void IFitObserver::notify(IObservable *subject)
{
    FitSuite *fit_suite = dynamic_cast<FitSuite *>(subject);
    if( !fit_suite ) throw NullPointerException("IFitObserver::update() -> Error! "
                                                "Can't access FitSuite");

    bool needs_update(false);

    if(m_current_strategy_index != (int)fit_suite->getNStrategy()) {
        needs_update = true;
        m_current_strategy_index = fit_suite->getNStrategy();
    }

    if( fit_suite->getNCalls() == 0 ) needs_update = true;  // first iteration
    if( fit_suite->isLastIteration() ) needs_update = true; // last iteration
    if( fit_suite->getNCalls() % m_update_every_nth == 0 ) needs_update = true; // every n'th iteration

    std::cout << "xxx " << fit_suite->getNCalls() << " fit_suite->isLastIteration():" << fit_suite->isLastIteration() << "needs:" << needs_update << std::endl;

    if(needs_update) update(fit_suite);

}

void IFitObserver::update(FitSuite *fit_suite)
{
    (void)fit_suite;
    throw NotImplementedException("IFitObserver::update(IObservable *subject) -> Error."
                                  "Not implemented.");
}

