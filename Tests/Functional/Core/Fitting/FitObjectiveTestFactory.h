// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/FitObjectiveTestFactory.h
//! @brief     Defines class FitObjectiveTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_FITOBJECTIVETESTFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_FITOBJECTIVETESTFACTORY_H

#include "Core/StandardSamples/IFactory.h"
#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! Factory to generate fitting tests. Tests will based on FitObjective approach.

class FitObjectiveTestFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    FitObjectiveTestFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_FITOBJECTIVETESTFACTORY_H
