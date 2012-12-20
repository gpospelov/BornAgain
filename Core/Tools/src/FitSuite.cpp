#include "FitSuite.h"
#include "Exceptions.h"
#include "FitParameterLinked.h"
#include "ParameterPool.h"
#include "Experiment.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"
#include <boost/bind.hpp>


FitSuite::FitSuite() : m_minimizer(0), m_is_last_iteration(false), m_n_call(0), m_n_strategy(0)
{
    m_function_chi2.init(this);
}


FitSuite::~FitSuite()
{
    clear();
}


/* ************************************************************************* */
// clear all data completely
/* ************************************************************************* */
void FitSuite::clear()
{
    m_fit_objects.clear();
    m_fit_parameters.clear();
    for(fitstrategies_t::iterator it = m_fit_strategies.begin(); it!= m_fit_strategies.end(); ++it) delete (*it);
    m_fit_strategies.clear();
    delete m_minimizer;
    m_minimizer = 0;
    m_is_last_iteration = false;
    m_n_call = 0;
    m_n_strategy = 0;
}


/* ************************************************************************* */
// add pair of (experiment, real data) for consecutive simulation
/* ************************************************************************* */
void FitSuite::addExperimentAndRealData(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module)
{
    m_fit_objects.add(experiment, real_data, chi2_module);
}


/* ************************************************************************* */
// add fit parameter
/* ************************************************************************* */
void FitSuite::addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim, double error)
{
    m_fit_parameters.addParameter(name, value, step, attlim, error);
}


/* ************************************************************************* */
// add fit strategy
/* ************************************************************************* */
void FitSuite::addFitStrategy(IFitSuiteStrategy *strategy)
{
    strategy->init(this);
    m_fit_strategies.push_back(strategy);
}


/* ************************************************************************* */
// Link defined FitMultiParameters with experiment parameters
/* ************************************************************************* */
void FitSuite::link_fit_parameters()
{
    ParameterPool *pool = m_fit_objects.createParameterTree();
    m_fit_parameters.link_to_pool(pool);
    std::cout << "FitSuite::link_fit_parameters() -> Parameter pool:" << std::endl;
    std::cout << *pool << std::endl;
    std::cout << "----------------" << std::endl;
    delete pool;
}


/* ************************************************************************* */
// run single minimization round
/* ************************************************************************* */
void FitSuite::minimize()
{
    // initializing minimizer with fitting functions
    //IMinimizer::function_chi2_t fun_chi2 = boost::bind(&FitSuite::fittingChiSquaredFunction, this, _1);
    IMinimizer::function_chi2_t fun_chi2 = boost::bind(&FitSuiteChiSquaredFunction::evaluate, &m_function_chi2, _1);

    IMinimizer::function_gradient_t fun_gradient = boost::bind(&FitSuite::fittingGradientFunction, this, _1, _2, _3);
    m_minimizer->setFunction( fun_chi2, m_fit_parameters.size(), fun_gradient, m_fit_objects.getSizeOfDataSet() );

    // initializing minimizer's parameters with the list of local fit parameters
    m_minimizer->setParameters(m_fit_parameters);

    // minimizing
    m_minimizer->minimize();
}


/* ************************************************************************* */
// run fit
/* ************************************************************************* */
bool FitSuite::check_prerequisites()
{
    if( !m_minimizer ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No minimizer found.");
    if( !m_fit_objects.size() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No experiment defined");
    if( !m_fit_parameters.size() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No fit parameters defined");
    return true;
}


/* ************************************************************************* */
// run fit
/* ************************************************************************* */
void FitSuite::runFit()
{
    // check if all prerequisites are fullfilled before starting minimization
    check_prerequisites();

    m_is_last_iteration = false;

    // linking fit parameters with parameters defined in the experiment
    link_fit_parameters();

    // running minimizer
    if( m_fit_strategies.empty() ) {
        // running single minimization round
        minimize();
    } else {
        // execute several minimization rounds as defined in concrete strategies
        for(fitstrategies_t::iterator it = m_fit_strategies.begin(); it!= m_fit_strategies.end(); ++it) {
            std::cout << "FitSuite::runFit() -> Info. Running strategy #" << m_n_strategy << " '" << (*it)->getName() << "'" << std::endl;
            (*it)->execute();
            m_n_strategy++;
        }
    }

    // seting parameters to the optimum values found by the minimizer
    for(size_t i=0; i<m_fit_parameters.size(); ++i) m_fit_parameters[i]->setValue(m_minimizer->getValueOfVariableAtMinimum(i));

    // calling observers again to let them to get results
    m_is_last_iteration = true;
    notifyObservers();
}


/* ************************************************************************* */
// function to minimize
/* ************************************************************************* */
double FitSuite::fittingChiSquaredFunction(const double *pars_current_values)
{
    std::cout << "FitSuite::functionToMinimize() -> Info" << std::endl;
    // set fitting parameters to values suggested by the minimizer
    m_fit_parameters.setValues(pars_current_values);

    // run simulations
    m_fit_objects.runSimulation();

    // caclulate chi2 value
    double chi_squared = m_fit_objects.getChiSquaredValue((int)m_fit_parameters.getNfreeParameters());

    notifyObservers();
    m_n_call++;
    return chi_squared;
}


/* ************************************************************************* */
// provides minimizer with gradients wrt parameters for single data element
/* ************************************************************************* */
double FitSuite::fittingGradientFunction(const double *pars_current_values, unsigned int index, double *deriv)
{
//    bool parameters_changed = m_fit_parameters.parametersDiffer(pars_current_values);

    throw 1;
    (void)pars_current_values;
    (void) deriv;
//    if(index % 10 == 0) std::cout << " elementFunction " << index << std::endl;
    // set fitting parameters to values suggested by the minimizer
    //m_fit_parameters.setValues(pars_current_values);

    // run simulations
    //m_fit_objects.getExperiment()->runSimulationElement(index);

    // caclulate residual value
//    m_fit_objects.getChiSquaredValue(m_fit_parameters.getNfreeParameters());
    double residual = m_fit_objects.getResidualValue(index);

//    if( deriv ) {
//        throw NotImplementedException("FitSuite::elementFunction() -> Error! Calculation of derivatives is not implemented");
//    }

    return residual;
}



