// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.cpp
//! @brief     Implements class IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMinimizer.h"

void IMinimizer::minimize()
{
    throw std::runtime_error("IMinimizer::minimize() -> Not implemented.");
}

std::string IMinimizer::minimizerName() const
{
    return std::string();
}

std::string IMinimizer::algorithmName() const
{
    return std::string();
}

void IMinimizer::setParameter(size_t /*index*/, const FitParameter* /*par*/)
{
    throw std::runtime_error("IMinimizer::setParameter() -> Not implemented.");
}

void IMinimizer::setParameters(const FitSuiteParameters & /*parameters*/)
{
    throw std::runtime_error("IMinimizer::setParameters() -> Not implemented.");
}

void IMinimizer::setChiSquaredFunction(function_chi2_t /*fun_chi2*/, size_t /*nparameters*/)
{
    throw std::runtime_error("IMinimizer::setChiSquaredFunction() -> Not implemented.");
}

void IMinimizer::setGradientFunction(function_gradient_t /*fun_gradient*/, size_t /*nparameters*/, size_t /*ndatasize*/)
{
    throw std::runtime_error("IMinimizer::setGradientFunction() -> Not implemented.");
}

size_t IMinimizer::getNumberOfVariables() const
{
    throw std::runtime_error("IMinimizer::getNumberOfVariables() -> Not implemented.");
}

double IMinimizer::getMinValue() const
{
    throw std::runtime_error("IMinimizer::getMinValue() -> Not implemented.");
}

double IMinimizer::getValueOfVariableAtMinimum(size_t /*index*/) const
{
    throw std::runtime_error("IMinimizer::getValueOfVariableAtMinimum() -> Not implemented.");
}

std::vector<double > IMinimizer::getValueOfVariablesAtMinimum() const
{
    throw std::runtime_error("IMinimizer::getValueOfVariablesAtMinimum() -> Not implemented.");
}

double IMinimizer::getErrorOfVariable(size_t /*index*/) const
{
    throw std::runtime_error("IMinimizer::getErrorOfVariable() -> Not implemented.");
}

std::vector<double> IMinimizer::getErrorOfVariables() const
{
    throw std::runtime_error("IMinimizer::getErrorOfVariables() -> Not implemented.");
}

void IMinimizer::clear()
{
    throw std::runtime_error("IMinimizer::clear() -> Not implemented.");
}

std::string IMinimizer::reportResults() const
{
    throw std::runtime_error("IMinimizer::reportResults() -> Not implemented.");
}


void IMinimizer::propagateResults(FitSuiteParameters &/*parameters*/)
{
    throw std::runtime_error("IMinimizer::propagateResults() -> Not implemented.");

}
