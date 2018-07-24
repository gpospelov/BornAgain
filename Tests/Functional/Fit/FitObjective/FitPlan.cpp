// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlan.h
//! @brief     Defines class FitPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitPlan.h"

FitPlan::FitPlan(const std::string& name)
    : MinimizerTestPlan(name)
{

}

bool FitPlan::checkMinimizer(Fit::Minimizer& minimizer)
{
    (void)minimizer;
    return true;
}
