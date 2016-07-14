// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitSuitePrintObserver.cpp
//! @brief     Implements class FitSuitePrintObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuite.h"
#include "FitSuiteParameters.h"
#include "FitSuiteStrategies.h"
#include "FitSuitePrintObserver.h"


FitSuitePrintObserver::FitSuitePrintObserver(int print_every_nth)
    : IFitObserver(print_every_nth)
    , m_fit_suite(0)
{
    m_last_call_time = boost::posix_time::second_clock::local_time();
}

void FitSuitePrintObserver::update(FitSuite *fit_suite)
{
    m_fit_suite = fit_suite;

    if(fit_suite->getNumberOfIterations() == 0) {
        m_start_time = boost::posix_time::second_clock::local_time();
        m_last_call_time = boost::posix_time::second_clock::local_time();
    }

    if(m_strategy_has_changed) {
        std::cout << "-------------------------------------------------------------------------------" << std::endl;
        std::cout << (*m_fit_suite->getFitStrategies()->getCurrentStrategy()) << std::endl;
        std::cout << "-------------------------------------------------------------------------------" << std::endl;
    }

    printIterationHeader();
    printWallTime();
    printParameters();

    if(fit_suite->isLastIteration()) {
        printFitResults();
    }
}

void FitSuitePrintObserver::printIterationHeader()
{
    std::cout << "FitPrintObserver::update() -> Info."
              << " NCall:" << m_fit_suite->getNumberOfIterations()
              << " NStrategy:" << m_fit_suite->getCurrentStrategyIndex()
              << " Chi2:" << std::scientific << std::setprecision(8)
              << m_fit_suite->getChi2() << std::endl;
}

void FitSuitePrintObserver::printWallTime()
{
    boost::posix_time::time_duration diff = boost::posix_time::microsec_clock::local_time() -
            m_last_call_time;
    std::cout << "Wall time since last call:"
              << std::fixed << std::setprecision(2)
              << diff.total_milliseconds()/1000. << " sec." <<std::endl;
    m_last_call_time = boost::posix_time::microsec_clock::local_time();
}

void FitSuitePrintObserver::printParameters()
{
    m_fit_suite->getFitParameters()->printParameters();
}

void FitSuitePrintObserver::printFitResults()
{
    std::cout << "This was the last iteration." << std::endl;
    m_fit_suite->printResults();
    boost::posix_time::time_duration  diff = boost::posix_time::second_clock::local_time() -
            m_start_time;
    std::cout << "Total time spend: "
              << std::fixed << std::setprecision(2)
              << diff.total_milliseconds()/1000. << " sec." <<std::endl;
    std::cout << std::endl;
}

