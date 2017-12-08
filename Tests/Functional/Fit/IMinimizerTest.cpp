// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IMinimizerTest.cpp
//! @brief     Implements class IMinimizerTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMinimizerTest.h"
#include "Units.h"

IMinimizerTest::IMinimizerTest(const std::string& minimizer_name,
                               const std::string& minimizer_algorithm)
    : IFittingTest(minimizer_name, minimizer_algorithm, "MiniGISAS", "CylindersInBABuilder")
{
}

IMinimizerTest::~IMinimizerTest() = default;

//! Creates plan with initial/real values of fit parameters.

void IMinimizerTest::initParameterPlan() {
  m_parplans.clear();
  m_parplans.push_back(std::make_unique<FitParameterPlan>("*Height", 4.5 * Units::nanometer,
                                          5.0 * Units::nanometer,
                                          AttLimits::lowerLimited(0.01), 0.01));
  m_parplans.push_back(std::make_unique<FitParameterPlan>("*Radius", 5.5 * Units::nanometer,
                                          5.0 * Units::nanometer,
                                          AttLimits::lowerLimited(0.01), 0.01));

  IFittingTest::initParameterPlan();
}
