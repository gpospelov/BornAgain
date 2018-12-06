// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IIntensityFunction.cpp
//! @brief     Implements the classes IntensityFunctionLog, IntensityFunctionSqrt
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IIntensityFunction.h"
#include <cmath>
#include <limits>

double IntensityFunctionLog::evaluate(double value) const
{
    return value > 0 ? std::log(value) : std::numeric_limits<double>::lowest();
}

double IntensityFunctionSqrt::evaluate(double value) const
{
    return value > 0 ? std::sqrt(value) : std::numeric_limits<double>::lowest();
}
