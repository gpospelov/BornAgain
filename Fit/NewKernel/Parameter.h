// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/Parameter.h
//! @brief     Defines class Parameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARAMETER_H
#define PARAMETER_H

#include "WinDllMacros.h"
#include "AttLimits.h"
#include <string>

namespace Fit {

//! A fittable parameter with value, error, step, and limits.
//! @ingroup fitting

class BA_CORE_API_ Parameter
{
public:
    Parameter();
    Parameter(const std::string& name, double value, const AttLimits& limits=AttLimits::limitless(),
              double step=0.0);

    std::string name() const;

    AttLimits limits() const;

    double value() const;

    double step() const;

private:
    std::string m_name;
    double m_start_value;
    double m_value;
    double m_step;
    double m_error;
    AttLimits m_limits;
};

}  // namespace Fit

#endif  // PARAMETER_H
