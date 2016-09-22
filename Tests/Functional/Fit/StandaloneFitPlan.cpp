// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandaloneFitPlan.cpp
//! @brief     Implements classes to define plans for testing standalone fit.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandaloneFitPlan.h"
#include "ObjectiveFunctionPlan.h"
#include <iostream>
#include <boost/format.hpp>
#include <cmath>


StandaloneFitPlan::StandaloneFitPlan(const std::string &minimizerName,
                                     const std::string &algorithmName,
                                     ObjectiveFunctionPlan *plan)
    : m_minimizerName(minimizerName)
    , m_algorithmName(algorithmName)
    , m_plan(plan){}

StandaloneFitPlan::~StandaloneFitPlan()
{

}

std::string StandaloneFitPlan::functionPlanName() const
{
    return m_plan->name();
}

objective_function_t StandaloneFitPlan::objectiveFunction() const
{
    return m_plan->objectiveFunction();
}

const std::vector<FitParameterPlan> &StandaloneFitPlan::parameterPlan() const
{
    return m_plan->parameterPlan();
}

//! Returns true if found values coincide with FitParameterPlan

bool StandaloneFitPlan::planSucceeded(const std::vector<double> &foundParValues)
{
    bool success(true);

    if(parameterPlan().size() != foundParValues.size())
        throw std::runtime_error("StandaloneFitPlan::planSucceeded() -> Error. Sizes differ.");

    for(size_t i=0; i<foundParValues.size(); ++i) {
        double expected_value = parameterPlan()[i].m_expected_value;
        double diff = std::abs(foundParValues[i] - expected_value)/expected_value;
        if (diff > parameterPlan()[i].m_threshold)
            success = false;

        std::string name = "par"+std::to_string(i);
        std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) %s\n") %
            name % foundParValues[i] % diff %
            (success ? "OK" : "FAILED");

    }

    return success;
}


