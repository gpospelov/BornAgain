// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitObjectiveTestFactory.h
//! @brief     Defines class FitObjectiveTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_FIT_FITOBJECTIVE_FITOBJECTIVETESTFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_FIT_FITOBJECTIVE_FITOBJECTIVETESTFACTORY_H

#include "Tests/Functional/TestMachinery/FunctionalTestFactory.h"

//! Factory to generate fitting tests. Tests will based on FitObjective approach.

class FitObjectiveTestFactory : public FunctionalTestFactory
{
public:
    FitObjectiveTestFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_FIT_FITOBJECTIVE_FITOBJECTIVETESTFACTORY_H
