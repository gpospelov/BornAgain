// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/ROOTMinimizer.cpp
//! @brief     Implements class ROOTMinimizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ROOTMinimizer.h"
#include "Exceptions.h"
#include "FitSuiteParameters.h"
#include "Utils.h"
#include "ROOTMinimizerFunction.h"
#include <iomanip>
#include <sstream>
#include <boost/assign/list_of.hpp>
#include <boost/assign/list_of.hpp>
#include "ROOTMinimizerHelper.h"
#include "MinimizerOptions.h"


#ifdef HAS_GENETIC_MINIMIZER
#include "Math/GeneticMinimizer.h"
#endif


// ----------------------------------------------------------------------------
// ROOTMinimizer c-tor
//
// FYI http://root.cern.ch/phpBB3/viewtopic.php?f=15&t=14230&p=61216&hilit=minimizer+precision#p61216
//     http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=9181&hilit=precision+tolerance
// ----------------------------------------------------------------------------
ROOTMinimizer::ROOTMinimizer(const std::string& minimizer_name, const std::string& algo_type)
    : m_minimizer_name(minimizer_name)
    , m_algo_type(algo_type)
    , m_root_minimizer(0)
    , m_chi2_func(0)
    , m_gradient_func(0)
{
//    if( m_minimizer_name == "GSLMultiFit") {
//        // hacked version of ROOT's GSL Levenberg-Marquardt minimizer
//        m_root_minimizer = new ROOT::Patch::GSLNLSMinimizer(2);
//    }else if( m_minimizer_name == "GSLSimAn") {
//        // hacked version of ROOT's GSL Simulated annealing minimizer
//        m_root_minimizer = new ROOT::Patch::GSLSimAnMinimizer();
//        // changing default options to more appropriate
//        setOptionString("ntries=100:niters=10:step_size=1.0:k=1:t_initial=50.0:mu=1.05:t_min=0.1");

//    }else if( m_minimizer_name == "Minuit2") {
//        m_root_minimizer = new ROOT::Minuit2::Minuit2Minimizer(algo_type.c_str());

//    } else if( m_minimizer_name == "GSLMultiMin") {
//        m_root_minimizer = new ROOT::Math::GSLMinimizer(algo_type.c_str());

//#ifdef HAS_GENETIC_MINIMIZER
//   } else if (m_minimizer_name ==  "Genetic") {
//      m_root_minimizer = new ROOT::Math::GeneticMinimizer();
//#endif

////    } else {
////        m_root_minimizer = ROOT::Math::Factory::CreateMinimizer(minimizer_name, algo_type );
//    }
//    if(!m_root_minimizer) {
//        throw LogicErrorException("Can't create minimizer with name '"+minimizer_name+"', algo '" + algo_type+"'");
//    }




}


ROOTMinimizer::~ROOTMinimizer()
{
    delete m_root_minimizer;
    delete m_chi2_func;
    delete m_gradient_func;
}

void ROOTMinimizer::setParameters(const FitSuiteParameters& parameters)
{
    size_t index(0);
    for(FitSuiteParameters::const_iterator it=parameters.begin(); it!=parameters.end(); ++it) {
        setParameter(index++, (*it) );
    }
    if( parameters.size() != getNumberOfVariables())  {
        std::ostringstream ostr;
        ostr << "ROOTMinimizer::setParameters() -> Error! Number of variables defined in minimizer (" << getNumberOfVariables() << ") ";
        ostr << "doesn't coincide with number of FitSuite's parameters (" << parameters.size() << ")";
        throw LogicErrorException(ostr.str());
    }
}


void ROOTMinimizer::setParameter(size_t index, const FitParameter *par)
{
    bool success;
    if( par->isFixed() ) {
        success=m_root_minimizer->SetFixedVariable((int)index, par->getName().c_str(), par->getValue());
    }else if(par->hasLowerAndUpperLimits() ) {
        success=m_root_minimizer->SetLimitedVariable((int)index, par->getName().c_str(), par->getValue(), par->getStep(), par->getLowerLimit(), par->getUpperLimit());
    } else if(par->hasLowerLimit() && !par->hasUpperLimit() ) {
        success=m_root_minimizer->SetLowerLimitedVariable((int)index, par->getName().c_str(), par->getValue(), par->getStep(), par->getLowerLimit());
    } else if( par->hasUpperLimit() && !par->hasLowerLimit() ) {
        success=m_root_minimizer->SetUpperLimitedVariable((int)index, par->getName().c_str(), par->getValue(), par->getStep(), par->getUpperLimit());
    } else if( !par->hasUpperLimit() && !par->hasLowerLimit() && !par->isFixed() ) {
        success=m_root_minimizer->SetVariable((int)index, par->getName().c_str(), par->getValue(), par->getStep());
    } else {
        throw DomainErrorException("ROOTMinimizer::setVariable() -> Error!");
    }

    if( !success ) {
        std::ostringstream ostr;
        ostr << "ROOTMinimizer::setVariable() -> Error! Minimizer returned false while setting the variable." << std::endl;
        ostr << "Probably given index has been already used for another variable name." << std::endl;
        ostr << "Index:" << index << " name '" << par->getName() << "'" << std::endl;
        throw LogicErrorException(ostr.str());
    }
}


void ROOTMinimizer::minimize()
{
    propagateOptions();
    m_root_minimizer->Minimize();
}


void ROOTMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)
{
    delete m_chi2_func;
    m_chi2_func = new ROOTMinimizerChiSquaredFunction(fun_chi2, (int)nparameters);
    if( !isGradientBasedAgorithm() ) m_root_minimizer->SetFunction(*m_chi2_func);
}

void ROOTMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)
{
    delete m_gradient_func;
    m_gradient_func = new ROOTMinimizerGradientFunction(fun_gradient, nparameters, ndatasize);
    if( isGradientBasedAgorithm() ) m_root_minimizer->SetFunction(*m_gradient_func);
}


std::vector<double > ROOTMinimizer::getValueOfVariablesAtMinimum() const
{
    std::vector<double > result;
    result.resize(getNumberOfVariables(), 0.0);
    std::copy(m_root_minimizer->X(), m_root_minimizer->X()+getNumberOfVariables(), result.begin());
    return result;
}


std::vector<double > ROOTMinimizer::getErrorOfVariables() const
{
    std::vector<double > result;
    result.resize(getNumberOfVariables(), 0.0);
    if(m_root_minimizer->Errors() != 0 ) {
        std::copy(m_root_minimizer->Errors(), m_root_minimizer->Errors()+getNumberOfVariables(), result.begin());
    }
    return result;
}


void ROOTMinimizer::printResults() const
{
    ROOTMinimizerHelper::printResults(this);
}


size_t ROOTMinimizer::getNCalls() const
{
    return m_root_minimizer->NCalls();
}


//MinimizerOptions &ROOTMinimizer::getOptions()
//{
//    return m_options;
//}


void ROOTMinimizer::setOptions(const MinimizerOptions &options)
{
    m_options = options;
    propagateOptions();
}

//void ROOTMinimizer::setOptions(const std::string& options)
//{
//    ROOTMinimizerHelper::setOptions(m_root_minimizer, options);
//}


void ROOTMinimizer::propagateOptions()
{
    m_root_minimizer->SetTolerance(m_options.getTolerance());
    m_root_minimizer->SetPrecision(m_options.getPrecision());
    m_root_minimizer->SetMaxFunctionCalls(m_options.getMaxFunctionCalls());
    m_root_minimizer->SetMaxIterations(m_options.getMaxIterations());
    m_root_minimizer->SetPrintLevel(m_options.getPrintLevel());
}



