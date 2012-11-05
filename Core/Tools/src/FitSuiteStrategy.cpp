#include "FitSuiteStrategy.h"
#include "FitSuite.h"
#include "Exceptions.h"
#include "OutputData.h"
#include "ChiSquaredModule.h"
#include "Experiment.h"
#include "GISASExperiment.h"
#include "IMinimizer.h"
#include "MathFunctions.h"
#include <iostream>



/* ************************************************************************* */
// Default fit strategy just let FitSuite to run it's minimization round
/* ************************************************************************* */
void FitSuiteStrategyDefault::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyDefault::execute() -> FitSuite doesn't exists");

    // calling minimization
    m_fit_suite->minimize();
}


/* ************************************************************************* */
// adjust (rebin) data before running fit suite minimization round
/* ************************************************************************* */
void FitSuiteStrategyAdjustData::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyAdjustData::execute() -> FitSuite doesn't exists");

    // if no data rediction was requested, just call FitSuite's minimization
    if( m_power_of_two == 0 ) {
        m_fit_suite->minimize();
        return;
    }

    // saving original data
    OutputData<double > *orig_data = m_fit_suite->getChiSquaredModule()->getRealData()->clone();
    // create adjusted data which will have doubled (4,8,...) bin size
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
    m_fit_suite->getMinimizer()->clear(); // clear minimizer's parameters and error matrixes
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
    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyAdjustParameters::execute() -> FitSuite doesn't exists");

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


/* ************************************************************************* */
// Helps minimizer get out of local minima by disturbing real data
/* ************************************************************************* */
void FitSuiteStrategyBootstrap::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyBootsrap::execute() -> FitSuite doesn't exists");

    std::vector<FitResult > fitHistory;

    // minimizing first time and saving initial parameters
    m_fit_suite->getMinimizer()->clear();
    m_fit_suite->minimize();

    vdouble1d_t param_values = getFitSuiteParameterValues();
    double chi2_last = m_fit_suite->getMinimizer()->getMinValue();

    FitResult fitResult;
//    fitResult.chi2 = m_fit_suite->getMinimizer()->getMinValue();
//    for(FitSuite::fitparameters_t::iterator it = m_fit_suite->fitparams_begin(); it!=m_fit_suite->fitparams_end(); ++it) {
//        fitResult.param_values.push_back( (*it)->getValue());
//        param_values.push_back( (*it)->getValue() );
//    }
//    fitHistory.push_back(fitResult);


    OutputData<double > *orig_data = m_fit_suite->getChiSquaredModule()->getRealData()->clone();
    for(int i_iter=0; i_iter<m_n_iterations; ++i_iter) {
        OutputData<double > *noisy_data = generateNoisyData(100, *orig_data);

        fitResult.clear();
        fitResult.niter = i_iter;
        fitResult.chi2_last = chi2_last;
        fitResult.param_values = param_values;

        std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.1 Iter: " << i_iter << " chi2_last:" << chi2_last;
        for(size_t i=0; i<param_values.size(); ++i) std::cout << " " << param_values[i];
        std::cout << std::endl;

        setFitSuiteParameterValues(param_values);

        // minimizing noisy data
        m_fit_suite->setRealData(*noisy_data);
        m_fit_suite->getMinimizer()->clear();
        m_fit_suite->minimize();
        double chi2_noisy = m_fit_suite->getMinimizer()->getMinValue();
        std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.2 Iter: " << i_iter << " chi2_noisy:" << chi2_noisy;
        vdouble1d_t param_values_noisy = getFitSuiteParameterValues();
        for(size_t i=0; i<param_values_noisy.size(); ++i) std::cout << " " << param_values_noisy[i];
        std::cout << std::endl;

        // minimizing original data (last parameters will be used as a starting value)
        m_fit_suite->setRealData(*orig_data);
        setFitSuiteParameterValues(param_values_noisy);
        m_fit_suite->getMinimizer()->clear();
        m_fit_suite->minimize();
        double chi2_current = m_fit_suite->getMinimizer()->getMinValue();

        std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.3 Iter: " << i_iter << " chi2_last:" << chi2_last << " chi2_noisy:" << chi2_noisy << " chi2_current:" << chi2_current;
        vdouble1d_t param_values_last = getFitSuiteParameterValues();
        for(size_t i=0; i<param_values_last.size(); ++i) std::cout << " " << param_values_last[i];
        std::cout << std::endl;

        fitResult.takethis = false;
        if(chi2_current <= chi2_last) {
            param_values = getFitSuiteParameterValues();
            std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.4 Iter: " << i_iter << " TAKING PARS:";
            for(size_t i=0; i<param_values.size(); ++i) std::cout << " " << param_values[i];
            std::cout << std::endl;
            fitResult.takethis = true;

        }

        fitResult.chi2_current = chi2_current;
        fitResult.chi2_noisy = chi2_noisy;
        fitResult.param_values_noisy = param_values_noisy;
        fitResult.param_values_last = param_values_last;
        fitHistory.push_back(fitResult);

        chi2_last = chi2_current;

        delete noisy_data;
    }

    std::cout << "FitSuiteStrategyBootstrap::execute() -> Results" << std::endl;
    for(size_t i=0; i<fitHistory.size(); ++i) {
        std::cout << "i:" << i
                  << " niter:" << fitHistory[i].niter
//                  << " chi2_last:" << fitHistory[i].chi2_last
//                  << " chi2_noisy:" << fitHistory[i].chi2_noisy
//                  << " chi2_current:" << fitHistory[i].chi2_current
                  << std::endl;
        std::cout << " chi2_last   :" << fitHistory[i].chi2_last << " |  ";
        for(size_t j=0; j<fitHistory[i].param_values.size(); ++j) std::cout << fitHistory[i].param_values[j] << " ";
        std::cout << std::endl;

        std::cout << " chi2_noisy  :" << fitHistory[i].chi2_noisy << " |  ";
        for(size_t j=0; j<fitHistory[i].param_values_noisy.size(); ++j) std::cout << fitHistory[i].param_values_noisy[j] << " ";
        std::cout << std::endl;

        std::cout << " chi2_current:" << fitHistory[i].chi2_current << " |  ";
        for(size_t j=0; j<fitHistory[i].param_values_last.size(); ++j) std::cout << fitHistory[i].param_values_last[j] << " ";
        std::cout << std::endl;
        std::cout << " take this:" << fitHistory[i].takethis << std::endl;
        std::cout << "--------------" << std::endl;
    }

}

// get current values of all parameters defined in FitSuite
std::vector<double > FitSuiteStrategyBootstrap::getFitSuiteParameterValues()
{
    std::vector<double > param_values;
    for(FitSuite::fitparameters_t::iterator it = m_fit_suite->fitparams_begin(); it!=m_fit_suite->fitparams_end(); ++it) {
        param_values.push_back( (*it)->getValue() );
    }
    return param_values;
}

// set new values of all parameters in FitSuite
void FitSuiteStrategyBootstrap::setFitSuiteParameterValues(const std::vector<double > &parvalues)
{
    if(parvalues.size() != m_fit_suite->fitparams_size()) {
        throw LogicErrorException("FitSuiteStrategyBootstrap::setFitSuiteParameterValues() -> Number of parameters in FitSuite doesn't coincide with request");
    }
    int index(0);
    for(FitSuite::fitparameters_t::iterator it = m_fit_suite->fitparams_begin(); it!=m_fit_suite->fitparams_end(); ++it) {
        (*it)->setValue(parvalues[index++]);
    }
}

// generate noisy data
OutputData<double> *FitSuiteStrategyBootstrap::generateNoisyData(double noise_factor, const OutputData<double> &source)
{
    OutputData<double> *p_result = source.clone();
    p_result->resetIndex();
    while (p_result->hasNext()) {
        double current = p_result->currentValue();
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        //std::cout << "XXX " << current << " " << random << " " << current/random << std::endl;
        if (random<0.0) random = 0.0;
        p_result->next() = random;
    }

//    OutputData<double> *p_result = source.clone();
//    p_result->resetIndex();
//    double random_factor = noise_factor*MathFunctions::GenerateNormalRandom(0.0, 1.0);

//    while (p_result->hasNext()) {
//        double current = p_result->currentValue();
//        double random = current + random_factor*current;
//        if (random<0.0) random = 0.0;
//        p_result->next() = random;
//        std::cout << random << " XXXXXX " << current << " " << random/current << std::endl;
//    }

    return p_result;
}

