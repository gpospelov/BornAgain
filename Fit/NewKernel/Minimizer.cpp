// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/Minimizer.cpp
//! @brief     Implements class Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Minimizer.h"
#include "Kernel.h"
#include "PyCallback.h"

using namespace Fit;

Minimizer::Minimizer()
    : m_kernel(new Kernel)
{

}

void Minimizer::setMinimizer(const std::string& minimizerName, const std::string& algorithmName,
                             const std::string& options)
{
    m_kernel->setMinimizer(minimizerName, algorithmName, options);
}

Minimizer::~Minimizer() = default;

MinimizerResult Minimizer::minimize(fcn_scalar_t fcn, const Parameters& parameters)
{
    return m_kernel->minimize(fcn, parameters);
}

MinimizerResult Minimizer::minimize(fcn_residual_t fcn, const Parameters& parameters)
{
    return m_kernel->minimize(fcn, parameters);
}

MinimizerResult Minimizer::minimize(PyCallback& callback, const Parameters& parameters)
{
    fcn_scalar_t fcn = [&](const Parameters& pars) {
        return callback.call(pars);
    };
    return minimize(fcn, parameters);
}
