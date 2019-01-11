// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IInterferenceFunction.cpp
//! @brief     Implements the interface class IInterferenceFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IInterferenceFunction.h"

#include <algorithm>
#include <stdexcept>

IInterferenceFunction::IInterferenceFunction()
    : m_position_var{0.0}
{}

IInterferenceFunction::~IInterferenceFunction() =default;

void IInterferenceFunction::setPositionVariance(double var)
{
    if (var < 0.0)
        throw std::runtime_error("IInterferenceFunction::setPositionVariance: "
                                 "variance should be positive.");
    m_position_var = var;
}

double IInterferenceFunction::DWfactor(kvector_t q)
{
    // remove z component for two dimensional interference functions:
    if (supportsMultilayer()) q.setZ(0.0);
    return std::exp(-q.mag2()*m_position_var);
}
