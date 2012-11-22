#include "FitSuiteStrategy.h"
#include "FitSuite.h"
#include "FitSuiteParameters.h"
#include "Exceptions.h"
#include "OutputData.h"
#include "IChiSquaredModule.h"
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
// TODO: refactor this all
void FitSuiteStrategyAdjustData::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyAdjustData::execute() -> FitSuite doesn't exists");

    // if no data rediction was requested, just call FitSuite's minimization
    if( m_power_of_two == 0 ) {
        if(m_call_minimize) {
            m_fit_suite->minimize();
        }
        return;
    }

    // adjusting real data for every experiment defined
    std::vector<OutputData<double > *> original_data_collection;
    for(size_t i_exp = 0; i_exp<m_fit_suite->getFitObjects()->size(); ++i_exp) {
        // saving original data
        OutputData<double > *orig_data = m_fit_suite->getFitObjects()->getRealData()->clone();
        original_data_collection.push_back(orig_data);

        // create adjusted data which will have doubled (2,4,8,...) bin size
        OutputData<double> *adjusted_data = orig_data;
        for(size_t i=0; i<m_power_of_two; ++i) {
            OutputData<double> *new_data = doubleBinSize(*adjusted_data);
            if(i!=0) {
                delete adjusted_data;
            }
            adjusted_data = new_data;
        }
        m_fit_suite->getFitObjects()->setRealData(*adjusted_data, i_exp);
        delete adjusted_data;
    }

    // calling minimization
    if(m_call_minimize) {
        m_fit_suite->getMinimizer()->clear(); // clear minimizer's parameters and error matrixes
        m_fit_suite->minimize();
    }

    // setting back original data
    if(m_preserve_original_data) {
        std::cout << "FitSuiteStrategyAdjustData::execute() -> Info. Returning original data back " << std::endl;
        for(size_t i_exp = 0; i_exp<m_fit_suite->getFitObjects()->size(); ++i_exp) {
            m_fit_suite->getFitObjects()->setRealData(*original_data_collection[i_exp], i_exp);
            delete original_data_collection[i_exp];
        }
    }

}


/* ************************************************************************* */
// strategy which fixes/releases fit parameters and then call minimizer
/* ************************************************************************* */
void FitSuiteStrategyAdjustParameters::execute()
{
    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyAdjustParameters::execute() -> FitSuite doesn't exists");
    FitSuiteParameters *fitParameters = m_fit_suite->getFitParameters();

    // fixing all parameters at they current values
    if( m_fix_all ) {
        for(FitSuiteParameters::iterator it = fitParameters->begin(); it!=fitParameters->end(); ++it) {
            std::cout << "FitSuiteStrategyAdjustParameters::execute() -> fixing " << (*it)->getName() << std::endl;
            (*it)->setFixed(true);
        }
    }

    // releasing all parameters
    if( m_release_all ) {
        for(FitSuiteParameters::iterator it = fitParameters->begin(); it!=fitParameters->end(); ++it) {
            std::cout << "FitSuiteStrategyAdjustParameters::execute() -> releasing " << (*it)->getName() << std::endl;
            (*it)->setFixed(false);
        }
    }

    // fixing dedicated list of fit parameters
    for(std::vector<std::string >::iterator it = m_pars_to_fix.begin(); it!= m_pars_to_fix.end(); ++it) {
        std::cout << "FitSuiteStrategyAdjustParameters::execute() -> fixing " << (*it) << std::endl;
        fitParameters->getParameter((*it))->setFixed(true);
    }

    // releasing dedicated list of fit parameters
    for(std::vector<std::string >::iterator it = m_pars_to_release.begin(); it!= m_pars_to_release.end(); ++it) {
        std::cout << "FitSuiteStrategyAdjustParameters::execute() -> releasing " << (*it) << std::endl;
        fitParameters->getParameter((*it))->setFixed(false);
    }

    // saving original param values
    std::vector<double > original_param_values = fitParameters->getValues();

    // calling minimization
    m_fit_suite->minimize();

    // returning parameters to original values as they were before minimization
    if(m_preserve_original_values) {
        fitParameters->setValues(original_param_values);
    }
}


/* ************************************************************************* */
// Helps minimizer get out of local minima by disturbing real data
/* ************************************************************************* */
void FitSuiteStrategyBootstrap::execute()
{
    throw NotImplementedException("FitSuiteStrategyBootstrap::execute()");

//    if( !m_fit_suite ) throw NullPointerException("FitSuiteStrategyBootsrap::execute() -> FitSuite doesn't exists");

//    std::vector<FitResult > fitHistory;

//    // minimizing first time and saving initial parameters
//    m_fit_suite->getMinimizer()->clear();
//    m_fit_suite->minimize();

//    vdouble1d_t param_values = getFitSuiteParameterValues();
//    double chi2_last = m_fit_suite->getMinimizer()->getMinValue();

//    FitResult fitResult;
//    OutputData<double > *orig_data = m_fit_suite->getChiSquaredModule()->getRealData()->clone();
//    for(int i_iter=0; i_iter<m_n_iterations; ++i_iter) {
//        OutputData<double > *noisy_data = generateNoisyData(10, *orig_data);

//        fitResult.clear();
//        fitResult.niter = i_iter;
//        fitResult.chi2_last = chi2_last;
//        fitResult.param_values = param_values;

//        std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.1 Iter: " << i_iter << " chi2_last:" << chi2_last;
//        for(size_t i=0; i<param_values.size(); ++i) std::cout << " " << param_values[i];
//        std::cout << std::endl;

//        setFitSuiteParameterValues(param_values);

//        // minimizing noisy data
//        m_fit_suite->setRealData(*noisy_data);
//        m_fit_suite->getMinimizer()->clear();
//        m_fit_suite->minimize();
//        double chi2_noisy = m_fit_suite->getMinimizer()->getMinValue();
//        std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.2 Iter: " << i_iter << " chi2_noisy:" << chi2_noisy;
//        vdouble1d_t param_values_noisy = getFitSuiteParameterValues();
//        for(size_t i=0; i<param_values_noisy.size(); ++i) std::cout << " " << param_values_noisy[i];
//        std::cout << std::endl;

//        // minimizing original data (last parameters will be used as a starting value)
//        m_fit_suite->setRealData(*orig_data);
//        setFitSuiteParameterValues(param_values_noisy);
//        m_fit_suite->getMinimizer()->clear();
//        m_fit_suite->minimize();
//        double chi2_current = m_fit_suite->getMinimizer()->getMinValue();

//        std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.3 Iter: " << i_iter << " chi2_last:" << chi2_last << " chi2_noisy:" << chi2_noisy << " chi2_current:" << chi2_current;
//        vdouble1d_t param_values_last = getFitSuiteParameterValues();
//        for(size_t i=0; i<param_values_last.size(); ++i) std::cout << " " << param_values_last[i];
//        std::cout << std::endl;

//        fitResult.takethis = false;
//        if(chi2_current <= chi2_last) {
//            param_values = getFitSuiteParameterValues();
//            std::cout << "FitSuiteStrategyBootstrap::execute() -> 1.4 Iter: " << i_iter << " TAKING PARS:";
//            for(size_t i=0; i<param_values.size(); ++i) std::cout << " " << param_values[i];
//            std::cout << std::endl;
//            fitResult.takethis = true;

//        }

//        fitResult.chi2_current = chi2_current;
//        fitResult.chi2_noisy = chi2_noisy;
//        fitResult.param_values_noisy = param_values_noisy;
//        fitResult.param_values_last = param_values_last;
//        fitHistory.push_back(fitResult);

//        chi2_last = chi2_current;

//        delete noisy_data;
//    }

//    std::cout << "FitSuiteStrategyBootstrap::execute() -> Results" << std::endl;
//    for(size_t i=0; i<fitHistory.size(); ++i) {
//        std::cout << "i:" << i << " niter:" << fitHistory[i].niter << std::endl;
//        std::cout << " chi2_last   :" << fitHistory[i].chi2_last << " |  ";
//        for(size_t j=0; j<fitHistory[i].param_values.size(); ++j) std::cout << fitHistory[i].param_values[j] << " ";
//        std::cout << std::endl;

//        std::cout << " chi2_noisy  :" << fitHistory[i].chi2_noisy << " |  ";
//        for(size_t j=0; j<fitHistory[i].param_values_noisy.size(); ++j) std::cout << fitHistory[i].param_values_noisy[j] << " ";
//        std::cout << std::endl;

//        std::cout << " chi2_current:" << fitHistory[i].chi2_current << " |  ";
//        for(size_t j=0; j<fitHistory[i].param_values_last.size(); ++j) std::cout << fitHistory[i].param_values_last[j] << " ";
//        std::cout << std::endl;
//        std::cout << " take this:" << fitHistory[i].takethis << std::endl;
//        std::cout << "--------------" << std::endl;
//    }

}


// generate noisy data
OutputData<double> *FitSuiteStrategyBootstrap::generateNoisyData(double noise_factor, const OutputData<double> &source)
{
    OutputData<double> *p_result = source.clone();
    OutputData<double>::iterator it = p_result->begin();
    while (it != p_result->end()) {
        double current = *it;
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        *it = random;
        ++it;
    }
    return p_result;
}

