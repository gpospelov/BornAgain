// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/SpecularFitTest.cpp
//! @brief     Implements class SpecularFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularFitTest.h"
#include "Units.h"
#include <sstream>

SpecularFitTest::SpecularFitTest()
    : IObsoleteFittingTest("Minuit2", "Migrad", "BasicSpecular", "PlainMultiLayerBySLDBuilder")
{
}

SpecularFitTest::~SpecularFitTest() = default;

void SpecularFitTest::initParameterPlan() // thickness of all odd layers as a parameter
{
  m_parplans.clear();
  FitParameter parameter(5.0, AttLimits::limited(1.0, 7.0), 0.1);
  const std::string prefix = "*";
  const std::string postfix = "/Thickness";
  for (unsigned odd = 1; odd < 10; odd = odd + 2) {
      std::ostringstream pattern;
      pattern << prefix << odd << postfix;
      parameter.addPattern(pattern.str());
  }
  m_parplans.push_back(std::make_unique<FitParameterPlan>(parameter, 3.0));
}
