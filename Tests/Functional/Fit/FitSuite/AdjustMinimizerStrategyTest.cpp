// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/AdjustMinimizerStrategyTest.cpp
//! @brief     Implements class AdjustMinimizerStrategyTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AdjustMinimizerStrategyTest.h"
#include "Units.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"
#include "AdjustMinimizerStrategy.h"
#include "MinimizerConstants.h"


AdjustMinimizerStrategyTest::AdjustMinimizerStrategyTest()
    : IObsoleteMinimizerTest("undefined", "undefined")
{}

void AdjustMinimizerStrategyTest::initParameterPlan()
{
    m_parplans.clear();
    m_parplans.push_back(std::make_unique<FitParameterPlan>("*Height", 2.0 * Units::nanometer,
                                                            5.0 * Units::nanometer,
                                                            AttLimits::limited(0.01, 30.0), 0.05));
    m_parplans.push_back(std::make_unique<FitParameterPlan>("*Radius", 10.0 * Units::nanometer,
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
