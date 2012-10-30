#include "FitSuiteStrategy.h"
#include "FitSuite.h"
#include "Exceptions.h"
#include <iostream>

/* ************************************************************************* */
//
/* ************************************************************************* */
void FitSuiteStrategyAdjustParameters::execute()
{
    if( !m_fit_suite ) throw NullPointerException("IFitSuiteStrategy::execute() -> FitSuite doesn't exists");

    // fixing all parameters at they current values
    if( m_fix_all ) {
        for(FitSuite::fitparameters_t::iterator it = m_fit_suite->fitparams_begin(); it!=m_fit_suite->fitparams_end(); ++it) {
            std::cout << "FitSuiteStrategyAdjustParameters::execute() -> fixing " << (*it)->getName() << std::endl;
            (*it)->setFixed(true);
        }
    }

    // releasing all parameters
    if( m_release_all ) {
        for(FitSuite::fitparameters_t::iterator it = m_fit_suite->fitparams_begin(); it!=m_fit_suite->fitparams_end(); ++it) {
            std::cout << "FitSuiteStrategyAdjustParameters::execute() -> releasing " << (*it)->getName() << std::endl;
            (*it)->setFixed(false);
        }
    }

    // fixing dedicated list of fit parameters
    for(std::vector<std::string >::iterator it = m_pars_to_fix.begin(); it!= m_pars_to_fix.end(); ++it) {
        std::cout << "FitSuiteStrategyAdjustParameters::execute() -> fixing " << (*it) << std::endl;
        m_fit_suite->getFitParameter((*it))->setFixed(true);
    }

    // releasing dedicated list of fit parameters
    for(std::vector<std::string >::iterator it = m_pars_to_release.begin(); it!= m_pars_to_release.end(); ++it) {
        std::cout << "FitSuiteStrategyAdjustParameters::execute() -> releasing " << (*it) << std::endl;
        m_fit_suite->getFitParameter((*it))->setFixed(false);
    }

    // calling minimization
    m_fit_suite->minimize();
}
