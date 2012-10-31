#include "FitSuiteStrategy.h"
#include "FitSuite.h"
#include "Exceptions.h"
#include "OutputData.h"
#include "ChiSquaredModule.h"
#include "Experiment.h"
#include "GISASExperiment.h"
#include "IMinimizer.h"
#include <iostream>



/* ************************************************************************* */
// Default fit strategy just let FitSuite to run it's minimization round
/* ************************************************************************* */
void FitSuiteStrategyDefault::execute()
{
    // calling minimization
    m_fit_suite->minimize();
}



/* ************************************************************************* */
// adjust data before running fit suite minimization round
/* ************************************************************************* */
void FitSuiteStrategyAdjustData::execute()
{
    // saving original data
    OutputData<double > *orig_data = m_fit_suite->getChiSquaredModule()->getRealData()->clone();

    OutputData<double> *adjusted_data = orig_data;
    for(size_t i=0; i<m_power_of_two; ++i) {
        OutputData<double> *new_data = doubleBinSize(*adjusted_data);
        if(i!=0) {
            delete adjusted_data;
        }
        adjusted_data = new_data;
    }

    // setting all up with new data
    m_fit_suite->setRealData(*adjusted_data);
    const NamedVector<double> *axis0 = reinterpret_cast<const NamedVector<double>*>(adjusted_data->getAxes()[0]);
    const NamedVector<double> *axis1 = reinterpret_cast<const NamedVector<double>*>(adjusted_data->getAxes()[1]);
    GISASExperiment *experiment = dynamic_cast<GISASExperiment *>(m_fit_suite->getExperiment());
    if( !experiment ) {
        throw NullPointerException("FitSuiteStrategyAdjustData::execute() -> Error! Can't get GISASExperiment.");
    }
    experiment->setDetectorParameters(axis0->getSize(), axis0->getMin(), axis0->getMax(), axis1->getSize(), axis1->getMin(), axis1->getMax());

    // calling minimization
    m_fit_suite->getMinimizer()->clear();

    m_fit_suite->minimize();

    // returning back original data
    m_fit_suite->setRealData(*orig_data);
    axis0 = reinterpret_cast<const NamedVector<double>*>(orig_data->getAxes()[0]);
    axis1 = reinterpret_cast<const NamedVector<double>*>(orig_data->getAxes()[1]);
    experiment->setDetectorParameters(axis0->getSize(), axis0->getMin(), axis0->getMax(), axis1->getSize(), axis1->getMin(), axis1->getMax());

    delete orig_data;
    delete adjusted_data;
}




/* ************************************************************************* */
// strategy which fixes/releases fit parameters and then call minimizer
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
