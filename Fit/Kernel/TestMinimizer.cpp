// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TrivialMinimizer.cpp
//! @brief     Implements class TrivialMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestMinimizer.h"
#include "FitParameter.h"
#include "MinimizerConstants.h"
#include <iostream>
#include <sstream>

std::string TestMinimizer::minimizerName() const
{
    return std::string(MinimizerNames::Test);
}

//! run minimization
void TestMinimizer::minimize()
{
    m_min_value = m_fcn(m_parameters.getValues());
}

//! Returns value of the parameter at the minimum
std::vector<double > TestMinimizer::getValueOfVariablesAtMinimum() const
{
    return m_parameters.getValues();
}

void TestMinimizer::setParameters(const FitSuiteParameters& parameters)
{
    m_parameters.clear();
    for(size_t i_par = 0; i_par<parameters.size(); ++i_par)
        m_parameters.addFitParameter(new FitParameter( *parameters[i_par] ) );
}

void TestMinimizer::setObjectiveFunction(objective_function_t func)
{
    m_fcn = func;
}

std::string TestMinimizer::reportResults() const
{
    std::ostringstream result;
    result << "TestMinimizer::printResult() -> Done. Objective function value = "
           << m_min_value << std::endl;
    return result.str();
}

std::vector<double> TestMinimizer::getErrorOfVariables() const
{
    std::vector<double> result;
    result.resize(m_parameters.size());
    return result;
}

void TestMinimizer::propagateResults(FitSuiteParameters &)
{

}


