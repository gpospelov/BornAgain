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
void FitSuite::addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim)
{
    m_fit_parameters.addParameter(name, value, step, attlim);
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
    // initializing minimizer with fcn function belonging to given class
    IMinimizer::function_t fcn = boost::bind(&FitSuite::functionToMinimize, this, _1);
    //m_minimizer->setFunction( fcn, (int)m_fit_parameters.size() );
    // FIXME: FitSuite::minimize() where to get number of elements?
    int nelements = m_fit_objects.getRealData()->getAllocatedSize();
    IMinimizer::element_function_t element_fcn = boost::bind(&FitSuite::elementFunction, this, _1, _2, _3);
    m_minimizer->setFunction( fcn, (int)m_fit_parameters.size(), element_fcn, nelements );

    // propagating values of local fit parameters to the minimizer's internal parameters
    for(size_t i_par = 0; i_par<m_fit_parameters.size(); i_par++) {
        std::cout << " i_par " << i_par << std::endl;
        m_minimizer->setVariable((int)i_par, m_fit_parameters[i_par] );
    }
    if( m_fit_parameters.size() != m_minimizer->getNumberOfVariables())  {
        std::ostringstream ostr;
        ostr << "FitSuite::minimize() -> Error! Number of variables defined in minimizer (" << m_minimizer->getNumberOfVariables() << ") ";
        ostr << "doesn't coincide with number of FitSuite's parameters (" << m_fit_parameters.size() << ")";
        throw LogicErrorException(ostr.str());
    }

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
double FitSuite::functionToMinimize(const double *pars_current_values)
{
    std::cout << " ffff " << std::endl;
    // set fitting parameters to values suggested by the minimizer
    m_fit_parameters.setValues(pars_current_values);

    // run simulations
    m_fit_objects.runSimulation();

    // caclulate chi2 value
    double chi_squared = m_fit_objects.getChiSquaredValue(m_fit_parameters.getNfreeParameters());

    notifyObservers();
    m_n_call++;
    return chi_squared;
}


/* ************************************************************************* */
// provides minimizer with gradients wrt parameters for single data element
/* ************************************************************************* */
double FitSuite::elementFunction(const double *pars_current_values, unsigned int index, double *deriv)
{
    if(index % 10 == 0) std::cout << " elementFunction " << index << std::endl;
    // set fitting parameters to values suggested by the minimizer
    m_fit_parameters.setValues(pars_current_values);

    // run simulations
    m_fit_objects.getExperiment()->runSimulationElement(index);

    // caclulate residual value
//    m_fit_objects.getChiSquaredValue(m_fit_parameters.getNfreeParameters());
    double residual = m_fit_objects.getResidualValue(index);

    if( deriv ) {
        throw NotImplementedException("FitSuite::elementFunction() -> Error! Calculation of derivatives is not implemented");
    }

    return residual;
}



