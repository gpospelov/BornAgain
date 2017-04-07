// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitParameterPlan.h
//! @brief     Declares class FitParameterPlan.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERPLAN_H
#define FITPARAMETERPLAN_H

#include "AttLimits.h"
#include "FitParameter.h"
#include <memory>

//! @class FitParameterPlan
//! @ingroup standard_samples
//! @brief The FitParameterPlan defines fit parameter settings and the value which has to be found
//! in the course of minimization.

class FitParameterPlan
{
public:
    FitParameterPlan(const std::string &name, double start_value, double expected_value,
                     const AttLimits &limits, double step);
    FitParameterPlan(const FitParameter& param, double expected_value, double tolerance = 0.01);

    FitParameterPlan(const FitParameterPlan& other) = delete;
    FitParameterPlan& operator=(const FitParameterPlan& other) = delete;

    const FitParameter& fitParameter() const;

    double expectedValue() const { return m_expected_value; }

    double tolerance() const { return m_tolerance; }
    void setTolerance(double tolerance) { m_tolerance = tolerance; }

private:
    double m_expected_value; //!< expected value to find in the fit
    double m_tolerance; //!< tolerance on found value wrt expected value
    std::unique_ptr<FitParameter> m_parameter;
};

#endif // FITPARAMETERPLAN_H
