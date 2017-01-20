// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/AdjustMinimizerStrategyTest.cpp
//! @brief     Implements class AdjustMinimizerStrategyTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AdjustMinimizerStrategyTest.h"
#include "Units.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"
#include "AdjustMinimizerStrategy.h"
#include "MinimizerConstants.h"


AdjustMinimizerStrategyTest::AdjustMinimizerStrategyTest()
    : IMinimizerTest("undefined", "undefined")
{}

void AdjustMinimizerStrategyTest::initParameterPlan()
{
    m_parplans.clear();
    m_parplans.push_back(new FitParameterPlan("*Height", 2.0 * Units::nanometer,
                                            5.0 * Units::nanometer,
                                            AttLimits::limited(0.01, 30.0), 0.05));
    m_parplans.push_back(new FitParameterPlan("*Radius", 10.0 * Units::nanometer,
                                            5.0 * Units::nanometer,
                                            AttLimits::limited(0.01, 30.0), 0.05));
}

std::unique_ptr<FitSuite> AdjustMinimizerStrategyTest::createFitSuite() {
  std::unique_ptr<FitSuite> result(new FitSuite());
  result->initPrint(50);

  result->addFitStrategy(AdjustMinimizerStrategy(
      MinimizerNames::Genetic, std::string(), "MaxIterations=2;RandomSeed=1"));

  result->addFitStrategy(AdjustMinimizerStrategy(MinimizerNames::Minuit2,
                                                 AlgorithmNames::Migrad));

  for (size_t i = 0; i < m_parplans.size(); ++i)
    result->addFitParameter(m_parplans[i]->fitParameter());
  return result;
}
