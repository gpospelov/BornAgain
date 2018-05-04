// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.cpp
//! @brief     Implements class IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IMinimizer.h"

double IMinimizer::minValue() const
{
    throw std::runtime_error("IMinimizer::minValue() -> Not implemented.");
}

void IMinimizer::propagateResults(FitParameterSet&)
{
    throw std::runtime_error("IMinimizer::propagateResults() -> Not implemented.");
}

void IMinimizer::propagateResults(Fit::Parameters&)
{
    throw std::runtime_error("IMinimizer::propagateResults() -> Not implemented.");
}

void IMinimizer::setOptions(const std::string&)
{
    throw std::runtime_error("IMinimizer::setOptions() -> Not implemented.");
}
