// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/IMinimizer.cpp
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
#include "MinimizerOptions.h"

void IMinimizer::minimize()
{
    throw std::runtime_error("IMinimizer::minimize() -> Not implemented.");
}

void IMinimizer::setParameter(size_t /*index*/, const FitParameter* /*par*/)
{
    throw std::runtime_error("IMinimizer::setParameter() -> Not implemented.");
}

void IMinimizer::setParameters(const FitSuiteParameters& /*parameters*/)
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

void IMinimizer::printResults() const
{
    throw std::runtime_error("IMinimizer::printResults() -> Not implemented.");
}

size_t IMinimizer::getNCalls() const
{
    throw std::runtime_error("IMinimizer::getNCalls() -> Not implemented.");
}

MinimizerOptions* IMinimizer::getOptions()
{
    throw std::runtime_error("IMinimizer::getOptions() -> Not implemented.");
}

const MinimizerOptions* IMinimizer::getOptions() const
{
    throw std::runtime_error("IMinimizer::getOptions() -> Not implemented.");
}

void IMinimizer::setOptions(const MinimizerOptions& /*options*/)
{
    throw std::runtime_error("IMinimizer::setOptions() -> Not implemented.");
}

void IMinimizer::setOptionString(const std::string& /*options*/)
{
    throw std::runtime_error("IMinimizer::setOptionString() -> Not implemented.");
}

bool IMinimizer::isGradientBasedAgorithm()
{
    throw std::runtime_error(
        "IMinimizer::isGradientBasedAlgorithm() -> Not implemented.");
}

std::string IMinimizer::getMinimizerName() const
{
    throw std::runtime_error("IMinimizer::getMinimizerName() -> Not implemented.");
}

std::string IMinimizer::getAlgorithmName() const
{
    throw std::runtime_error("IMinimizer::getAlgorithmName() -> Not implemented.");
}
