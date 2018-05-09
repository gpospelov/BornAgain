// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/KernelTypes.h
//! @brief     Defines common types for fitting library.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef KERNELTYPES_H
#define KERNELTYPES_H

#include <functional>
#include <vector>

namespace Fit { class Parameters; }

typedef std::function<double(const std::vector<double>&)> objective_function_t;

typedef std::function<double(const std::vector<double>&, unsigned int, std::vector<double>&)>
    gradient_function_t;

typedef std::function<double(const double*)> root_objective_t;

typedef std::function<double(const double*, unsigned int, double*)> root_gradient_t;

using fcn_scalar_t = std::function<double(const Fit::Parameters&)>;
using fcn_residual_t = std::function<std::vector<double>(std::vector<double>)>;

#endif // KERNELTYPES_H
