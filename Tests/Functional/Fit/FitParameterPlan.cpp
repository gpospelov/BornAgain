// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitParameterPlan.cpp
//! @brief     Declares class FitParameterPlan.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterPlan.h"

FitParameterPlan::FitParameterPlan()
    : m_name(std::string())
    , m_start_value(0.0)
    , m_expected_value(0.0)
    , m_limits(AttLimits::limitless())
    , m_step(0.0)
    , m_threshold(0.0)
{

}

FitParameterPlan::FitParameterPlan(const std::string &name, double start_value,
                                   double expected_value,
                                   const AttLimits &limits, double step)
    : m_name(name)
    , m_start_value(start_value)
    , m_expected_value(expected_value)
    , m_limits(limits)
    , m_step(step)
    , m_threshold(0.01)
{

}
