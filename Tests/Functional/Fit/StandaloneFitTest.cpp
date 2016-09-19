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
#include "ObjectiveTestFunctions.h"
#include <iostream>

StandaloneFitTest::StandaloneFitTest()
    : IFunctionalTest("StandaloneFit", "Collection of standalone tests for fitting library")
{

}

bool StandaloneFitTest::runTest()
{
    std::unique_ptr<FitKernel> fitKernel(new FitKernel);

    fitKernel->setMinimizer("Minuit2", "Migrad");

//    void addFitParameter(const std::string& name, double value,
//                         const RealLimits& lim, const Attributes& attr,
//                         double step=0.0);


    fitKernel->addFitParameter("par1", -1.2, AttLimits::limited(-5.0, 5.0), 0.01);
    fitKernel->addFitParameter("par2", 1.0, AttLimits::limited(-5.0, 5.0), 0.01);


    fitKernel->setObjectiveFunction(TestFunctions::RosenBrock);
    fitKernel->minimize();

    std::cout << fitKernel->reportResults() << std::endl;

    return true;
}
