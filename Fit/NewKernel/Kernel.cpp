// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/Kernel.cpp
//! @brief     Implements class Kernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Kernel.h"
#include "MinimizerFactory.h"
#include "IMinimizer.h"

using namespace Fit;

namespace {
    const std::string default_minimizer = "Minuit2";
    const std::string default_algorithm = "Migrad";
}

Kernel::Kernel()
{
    setMinimizer(default_minimizer, default_algorithm);
}

Kernel::~Kernel() = default;

void Kernel::setMinimizer(const std::string& minimizerName, const std::string& algorithmName)
{
    m_minimizer.reset(MinimizerFactory::createMinimizer(minimizerName, algorithmName));
}

void Kernel::minimize(fcn_scalar_t fcn, const Parameters& parameters)
{
    setParameters(parameters);
    m_minimizer->minimize_scalar(fcn, parameters);
}

void Kernel::setParameters(const Parameters& parameters)
{
    m_parameters = parameters;
}
