// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/Kernel.h
//! @brief     Defines class Kernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef KERNEL_H
#define KERNEL_H

#include "WinDllMacros.h"
#include "Parameters.h"
#include "KernelTypes.h"
#include <functional>
#include <vector>
#include <memory>

class IMinimizer;

namespace Fit {

//! A main class to run fitting.
//! @ingroup fitting

class BA_CORE_API_ Kernel
{
public:
    Kernel();
    ~Kernel();

    void setMinimizer(const std::string& minimizerName, const std::string& algorithmName = "");

    void minimize(fcn_scalar_t fcn, const Parameters& parameters);

private:
    void setParameters(const Parameters& parameters);

    Parameters m_parameters;
    std::unique_ptr<IMinimizer> m_minimizer;
};

}  // namespace Fit

#endif  // KERNEL_H
