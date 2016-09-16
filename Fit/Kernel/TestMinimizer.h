// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TestMinimizer.h
//! @brief     Defines class TestMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTMINIMIZER_H
#define TESTMINIMIZER_H

#include "IMinimizer.h"
class FitParameterSet;

//! @class TestMinimizer
//! @ingroup fitting_internal
//! @brief Minimizer which calls minimization function once to test whole chain.

class BA_CORE_API_ TestMinimizer : public IMinimizer
{
 public:
    TestMinimizer() : m_min_value(0) {}
    ~TestMinimizer(){}

    virtual std::string minimizerName() const;

    void minimize();

    void setParameters(const FitParameterSet &parameters);

    void setObjectiveFunction(objective_function_t func);

    std::string reportResults() const override;

 private:
    double m_min_value;
    std::vector<double> m_parameter_values;
    objective_function_t m_fcn;
};

#endif
