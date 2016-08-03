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

#include "TrivialMinimizer.h"
#include "FitParameter.h"
#include <iostream>

//! run minimization
void TrivialMinimizer::minimize()
{
    m_min_value = m_fcn(&m_parameters.getValues()[0]);
}

//! Returns pointer to the parameters values at the minimum
double TrivialMinimizer::getValueOfVariableAtMinimum(size_t index) const
{
    return m_parameters[index]->getValue();
}

//! Returns value of the parameter at the minimum
std::vector<double > TrivialMinimizer::getValueOfVariablesAtMinimum() const
{
    return m_parameters.getValues();
}

void TrivialMinimizer::setParameters(const FitSuiteParameters& parameters)
{
    m_parameters.clear();
    for(size_t i_par = 0; i_par<parameters.size(); ++i_par)
        m_parameters.push_back(new FitParameter( *parameters[i_par] ) );
}

void TrivialMinimizer::printResults() const
{
    std::cout << "TrivialMinimizer::printResult() "  << m_min_value << std::endl;
}

std::vector<double> TrivialMinimizer::getErrorOfVariables() const
{
    std::vector<double> result;
    result.resize(m_parameters.size());
    return result;
}

std::string TrivialMinimizer::getMinimizerName() const
{
    return std::string("Test");
}

std::string TrivialMinimizer::getAlgorithmName() const
{
    return std::string();
}

MinimizerOptions *TrivialMinimizer::getOptions()
{
    return nullptr;
}

const MinimizerOptions *TrivialMinimizer::getOptions() const
{
    return nullptr;
}
