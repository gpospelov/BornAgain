// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/ObjectiveFunctionPlan.cpp
//! @brief     Declares classes to define plans for testing objective functions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ObjectiveFunctionPlan.h"
#include "ObjectiveTestFunctions.h"

ObjectiveFunctionPlan::ObjectiveFunctionPlan(const std::string &name, objective_function_t func,
                                             double , double )
    : m_name(name)
    , m_objective_function(func)
{

}

void ObjectiveFunctionPlan::addParameter(double start_value, double expected_value,
                                         const AttLimits &limits, double step)
{
    std::string name = "par"+std::to_string(m_parameters.size());
    m_parameters.push_back(FitParameterPlan(name, start_value, expected_value, limits, step));
}

//! Plan for finding rosenbrock function minimum
//! start point: F(-1.2,1.0) = 24.20
//! minimum    : F(1.0,1.0)  = 0.

Rosenbrock1::Rosenbrock1()
    : ObjectiveFunctionPlan("Rosenbrock1", TestFunctions::RosenBrock, 0.0)
{
    addParameter(-1.2, 1.0, AttLimits::limited(-5.0, 5.0), 0.01);
    addParameter(1.0,  1.0, AttLimits::limited(-5.0, 5.0), 0.01);
}

//! Plan for WoodFour function
//!   start point: F(-3,-1,-3,-1) = 19192
//!   minimum    : F(1,1,1,1)  =   0.

WoodFour::WoodFour()
    : ObjectiveFunctionPlan("WoodFour", TestFunctions::WoodFour, 0.0)
{
    addParameter(-3.0, 1.0, AttLimits::limited(-5.0, 5.0), 0.01);
    addParameter(-1.0, 1.0, AttLimits::limited(-5.0, 5.0), 0.01);
    addParameter(-3.0, 1.0, AttLimits::limited(-5.0, 5.0), 0.01);
    addParameter(-1.0, 1.0, AttLimits::limited(-5.0, 5.0), 0.01);
}

