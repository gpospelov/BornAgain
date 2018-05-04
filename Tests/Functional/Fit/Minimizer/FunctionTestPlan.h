// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/FunctionTestPlan.h
//! @brief     Defines class FunctionTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FUNCTIONTESTPLAN_H
#define FUNCTIONTESTPLAN_H

#include "KernelTypes.h"
#include "ParameterPlan.h"
#include <memory>
#include <vector>

namespace Fit { class Parameter; class Parameters;}

//! Defines objective function to fit, expected minimum, initial fit parameters and
//! expected values of fit parameters at minimum.

class FunctionTestPlan
{
public:
    FunctionTestPlan(const std::string &name, fcn_scalar_t func, double expected_minimum);

    virtual ~FunctionTestPlan();

    void addParameter(const Fit::Parameter& param, double expected_value, double tolerance = 0.01);

    fcn_scalar_t scalarFunction() const { return m_objective_function; }

    std::string name() const { return m_name; }

    Fit::Parameters parameters() const;

    bool valuesAsExpected(const std::vector<double>& values) const;

    bool minimumAsExpected(double found_minimum, double tolerance = 0.01) const;

private:
    std::string m_name; //!< plan name
    fcn_scalar_t m_objective_function; //!< objective function to minimize
    std::vector<ParameterPlan> m_parameter_plan; //! initial/expected parameter values
    double m_expected_minimum; //!< expected function minimum
};


class ScalarTestPlan : public FunctionTestPlan
{
public:
    ScalarTestPlan(const std::string &name, fcn_scalar_t func, double expected_minimum);

};

#endif // OBJECTIVEFUNCTIONPLAN_H
