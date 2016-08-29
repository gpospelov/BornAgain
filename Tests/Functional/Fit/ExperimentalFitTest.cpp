// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/ExperimentalFitTest.cpp
//! @brief     Implements class ExperimentalFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ExperimentalFitTest.h"
#include "Minuit2Minimizer.h"
#include "FitSuite.h"

ExperimentalFitTest::ExperimentalFitTest()
    : IMinimizerTest("Minuit2", "Migrad")
{}

std::unique_ptr<FitSuite> ExperimentalFitTest::createFitSuite()
{
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(10);
    result->setMinimizer( new Minuit2Minimizer() );
    for (const auto& par: m_parameters)
        result->addFitParameter(
            par.m_name, par.m_start_value,
            RealLimits::lowerLimited(0.01), Attributes::free(), par.m_start_value/100.);
    return result;
}
