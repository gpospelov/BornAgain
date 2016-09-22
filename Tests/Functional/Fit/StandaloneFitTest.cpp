// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandaloneFitTest.cpp
//! @brief     Implements class StandaloneFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandaloneFitTest.h"
#include "FitKernel.h"
#include "AttLimits.h"
#include "ObjectiveFunctionPlan.h"
#include "FitParameterSet.h"
#include <iostream>

StandaloneFitTest::StandaloneFitTest()
    : IFunctionalTest("StandaloneFit", "Collection of standalone tests for fitting library")
{
    addTest<Rosenbrock1>("Minuit2", "Migrad");
    addTest<WoodFour>("Minuit2", "Migrad");
    addTest<Rosenbrock1>("GSLMultiMin", "BFGS2");
}

bool StandaloneFitTest::runTest()
{
    bool success(true);
    for(auto plan: m_plans) {
        std::cout << plan->minimizerName()
                  << " " << plan->algorithmName()
                  << " " << plan->functionPlanName() << std::endl;

        success &= runPlan(plan);
    }

    std::cout << "StandaloneFitTest::runTest() -> " << (success ? "OK" : "FAILED") << std::endl;

    return success;
}

bool StandaloneFitTest::runPlan(std::shared_ptr<StandaloneFitPlan> plan)
{
    bool success(true);

    std::unique_ptr<FitKernel> fitKernel(new FitKernel);
    fitKernel->setMinimizer(plan->minimizerName(), plan->algorithmName());

    int index(0);
    for(FitParameterPlan p : plan->parameterPlan())
        fitKernel->addFitParameter("par"+std::to_string(index++), p.m_start_value, p.m_limits, p.m_step);

    fitKernel->setObjectiveFunction(plan->objectiveFunction());
    fitKernel->minimize();
    std::cout << fitKernel->reportResults() << std::endl;

    std::vector<double> foundValues = fitKernel->fitParameters()->values();

    if(!plan->planSucceeded(foundValues))
        success = false;

    return success;
}
