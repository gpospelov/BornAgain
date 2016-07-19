// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IIntensityFunction.cpp
//! @brief     Implements the classes IntensityFunctionLog, IntensityFunctionSqrt
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IIntensityFunction.h"
#include <cmath>

double IntensityFunctionLog::evaluate(double value) const
{
    return value > 0 ? std::log(value) : 0;
}

double IntensityFunctionSqrt::evaluate(double value) const
{
    return value > 0 ? std::sqrt(value) : 0;
}
