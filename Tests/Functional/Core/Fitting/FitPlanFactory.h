// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/FitPlanFactory.h
//! @brief     Defines class FitPlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_FITPLANFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_FITPLANFACTORY_H

#include "Fit/TestEngine/IFactory.h"
#include "Fit/TestEngine/MinimizerTestPlan.h"

//! Factory to generate plans for fitting with FitObjective.

class FitPlanFactory : public IFactory<std::string, MinimizerTestPlan>
{
public:
    FitPlanFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_FITPLANFACTORY_H
