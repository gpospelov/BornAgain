// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/IMinimizer.cpp
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

void IMinimizer::clear()
{
    throw std::runtime_error("IMinimizer::clear() -> Not implemented.");
}

void IMinimizer::setParameters(const FitParameterSet&)
{
    throw std::runtime_error("IMinimizer::setParameters() -> Not implemented.");
}

double IMinimizer::minValue() const
{
    throw std::runtime_error("IMinimizer::minValue() -> Not implemented.");
}

std::string IMinimizer::reportResults() const
{
    throw std::runtime_error("IMinimizer::reportResults() -> Not implemented.");
}

void IMinimizer::propagateResults(FitParameterSet&)
{
    throw std::runtime_error("IMinimizer::propagateResults() -> Not implemented.");
}

void IMinimizer::setOptions(const std::string&)
{
    throw std::runtime_error("IMinimizer::setOptions() -> Not implemented.");
}
