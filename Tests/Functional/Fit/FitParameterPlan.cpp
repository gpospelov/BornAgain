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

FitParameterPlan::FitParameterPlan(const std::string &name, double start_value,
                                   double expected_value,
                                   const AttLimits &limits, double step)
    : m_expected_value(expected_value)
    , m_tolerance(0.01)
{
    m_parameter.reset(new FitParameter(name, start_value, limits, step));
    m_parameter->setName(name);
}

FitParameterPlan::FitParameterPlan(const FitParameter& param, double expected_value,
                                   double tolerance)
    : m_expected_value(expected_value)
    , m_tolerance(tolerance)
    , m_parameter(param.clone())
{

}

const FitParameter& FitParameterPlan::fitParameter() const
{
    return *m_parameter;
}
