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

#ifndef FITPLAN_H
#define FITPLAN_H

#include "MinimizerTestPlan.h"

//! Contains all logic to construct FitObjective, setup Minimizer and check minimization results.

class FitPlan : public MinimizerTestPlan
{
public:
    FitPlan(const std::string& name);

    virtual bool checkMinimizer(Fit::Minimizer& minimizer);

};

#endif // FITPLAN_H
