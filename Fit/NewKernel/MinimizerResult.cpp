// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/MinimizerResult.cpp
//! @brief     Implements class MinimizerResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerResult.h"
#include "MinimizerResultsHelper.h"
#include <sstream>

using namespace Fit;

MinimizerResult::MinimizerResult()
    : m_min_value(0.0)
{

}

void MinimizerResult::setParameters(const Parameters& parameters)
{
    m_parameters = parameters;
}

Parameters MinimizerResult::parameters() const
{
    return m_parameters;
}

void MinimizerResult::setMinValue(double value)
{
    m_min_value = value;
}

//! Minimum value of objective function found by minimizer.

double MinimizerResult::minValue() const
{
    return m_min_value;
}

//! Returns multi-line string representing minimization results.

std::string MinimizerResult::toString() const
{
    std::ostringstream result;
    result << m_minimizer_report
           << MinimizerResultsHelper::reportParameters(m_parameters);
    return result.str();
}

void MinimizerResult::setReport(const std::string& value)
{
    m_minimizer_report = value;
}
