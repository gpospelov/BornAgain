// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitSuitePrintObserver.cpp
//! @brief     Implements class FitSuitePrintObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuitePrintObserver.h"
#include "FitSuite.h"


FitSuitePrintObserver::FitSuitePrintObserver(int print_every_nth)
    : m_fit_suite(0)
    , m_print_every_nth(print_every_nth)
    , m_previous_strategy_index(-1)
    , m_start_time()
    , m_last_call_time()
    , m_strategy_is_changed(false)
{
	m_last_call_time = boost::posix_time::second_clock::local_time();
}

void FitSuitePrintObserver::update(IObservable *subject)
{
    m_fit_suite = dynamic_cast<FitSuite *>(subject);
    if( !m_fit_suite ) throw NullPointerException("FitSuiteObserverPrint::update() -> Error! Can't access FitSuite");

    if(skipIteration()) return;

    if(m_fit_suite->getFitStrategies()->size() && m_strategy_is_changed) {
        std::cout << "-------------------------------------------------------------------------------" << std::endl;
        std::cout << "CurrentStrategyName: '"<< m_fit_suite->getFitStrategies()->getCurrentStrategyName() << "'" << std::endl;
        std::cout << "-------------------------------------------------------------------------------" << std::endl;
    }

    std::cout << "FitSuitePrintObserver::update() -> Info."
              << " NCall:" << m_fit_suite->getNCalls()
              << " NStrategy:" << m_fit_suite->getNStrategy()
              << " Chi2:" << std::scientific << std::setprecision(8)
              << m_fit_suite->getFitObjects()->getChiSquaredValue() << std::endl;

    boost::posix_time::time_duration diff = boost::posix_time::microsec_clock::local_time() - m_last_call_time;
    std::cout << "Wall time since last call:"
              << std::fixed << std::setprecision(2)
              << diff.total_milliseconds()/1000. << " sec." <<std::endl;
    m_last_call_time = boost::posix_time::microsec_clock::local_time();

    m_fit_suite->getFitParameters()->printParameters();

    if(m_fit_suite->isLastIteration()) {
        std::cout << "This was the last iteration." << std::endl;
        m_fit_suite->printResults();
        diff = boost::posix_time::second_clock::local_time() - m_start_time;
        std::cout << "Total time spend: "
                  << std::fixed << std::setprecision(2)
                  << diff.total_milliseconds()/1000. << " sec." <<std::endl;
    }
}


// return false if given iteration is
//   * the first iteration
//   * the last iteration
//   * n-th iteration
//   * strategy changed
bool FitSuitePrintObserver::skipIteration()
{
    if(m_fit_suite->getNCalls() == 0 ) {
        m_start_time = boost::posix_time::second_clock::local_time();
        m_last_call_time = boost::posix_time::second_clock::local_time();
    }

    checkStrategy();

    if( m_fit_suite->getNCalls() == 0 ) return false;  // first iteration
    if( m_fit_suite->isLastIteration() ) return false; // last iteration
    if( m_fit_suite->getNCalls() % m_print_every_nth == 0 ) return false; // every n'th iteration
    if(m_strategy_is_changed) return false; // strategy is changed

    return true;
}


void FitSuitePrintObserver::checkStrategy()
{
    m_strategy_is_changed = false;
    if(m_previous_strategy_index != (int)m_fit_suite->getNStrategy()) {
        m_previous_strategy_index = m_fit_suite->getNStrategy();
        m_strategy_is_changed = true;
    }
}


