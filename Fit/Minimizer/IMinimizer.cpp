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
    throw Exceptions::NotImplementedException("IMinimizer::minimize() -> Not implemented.");
}

void IMinimizer::setParameter(size_t /*index*/, const FitParameter* /*par*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setParameter() -> Not implemented.");
}

void IMinimizer::setParameters(const FitSuiteParameters& /*parameters*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setParameters() -> Not implemented.");
}

void IMinimizer::setChiSquaredFunction(function_chi2_t /*fun_chi2*/, size_t /*nparameters*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setChiSquaredFunction() -> Not implemented.");
}

void IMinimizer::setGradientFunction(function_gradient_t /*fun_gradient*/, size_t /*nparameters*/, size_t /*ndatasize*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setGradientFunction() -> Not implemented.");
}

size_t IMinimizer::getNumberOfVariables() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getNumberOfVariables() -> Not implemented.");
}

double IMinimizer::getMinValue() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getMinValue() -> Not implemented.");
}

double IMinimizer::getValueOfVariableAtMinimum(size_t /*index*/) const
{
    throw Exceptions::NotImplementedException("IMinimizer::getValueOfVariableAtMinimum() -> Not implemented.");
}

std::vector<double > IMinimizer::getValueOfVariablesAtMinimum() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getValueOfVariablesAtMinimum() -> Not implemented.");
}

double IMinimizer::getErrorOfVariable(size_t /*index*/) const
{
    throw Exceptions::NotImplementedException("IMinimizer::getErrorOfVariable() -> Not implemented.");
}

std::vector<double> IMinimizer::getErrorOfVariables() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getErrorOfVariables() -> Not implemented.");
}

void IMinimizer::clear()
{
    throw Exceptions::NotImplementedException("IMinimizer::clear() -> Not implemented.");
}

void IMinimizer::printResults() const
{
    throw Exceptions::NotImplementedException("IMinimizer::printResults() -> Not implemented.");
}

size_t IMinimizer::getNCalls() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getNCalls() -> Not implemented.");
}

MinimizerOptions* IMinimizer::getOptions()
{
    throw Exceptions::NotImplementedException("IMinimizer::getOptions() -> Not implemented.");
}

const MinimizerOptions* IMinimizer::getOptions() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getOptions() -> Not implemented.");
}

void IMinimizer::setOptions(const MinimizerOptions& /*options*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setOptions() -> Not implemented.");
}

void IMinimizer::setOptionString(const std::string& /*options*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setOptionString() -> Not implemented.");
}

bool IMinimizer::isGradientBasedAgorithm()
{
    throw Exceptions::NotImplementedException(
        "IMinimizer::isGradientBasedAlgorithm() -> Not implemented.");
}

std::string IMinimizer::getMinimizerName() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getMinimizerName() -> Not implemented.");
}

std::string IMinimizer::getAlgorithmName() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getAlgorithmName() -> Not implemented.");
}
