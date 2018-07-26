// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlanCases.h
//! @brief     Implements collection of FitPlanCases classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitPlanCases.h"
#include "Units.h"

using namespace Fit;

namespace {
    const double nm = Units::nanometer;
}

CylindersInBAPlan::CylindersInBAPlan()
    : FitPlan("CylindersInBAPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    addParameter(Parameter("height", 4.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
}

CylindersInBAEasyPlan::CylindersInBAEasyPlan()
    : FitPlan("CylindersInBAPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    const double tolerance = 0.1;
    addParameter(Parameter("height", 4.5*nm, AttLimits::limited(4.0, 6.0), 0.01),
                 5.0*nm, tolerance);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limited(4.0, 6.0), 0.01),
                 5.0*nm, tolerance);
}

CylindersInBAResidualPlan::CylindersInBAResidualPlan()
    : FitPlan("CylindersInBAResidualPlan", /*residual_based*/true)
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    addParameter(Parameter("height", 4.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
}
