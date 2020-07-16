// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/FunctionalTestFactory.h
//! @brief     Defines and implements FunctionalTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_FUNCTIONALTESTFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_FUNCTIONALTESTFACTORY_H

#include "Core/StandardSamples/IFactory.h"
#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! Simple factory to hold packs of functional tests.

class BA_CORE_API_ FunctionalTestFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    std::unique_ptr<IFunctionalTest> createTest(std::string& test_name)
    {
        return createItemPtr(test_name);
    }
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_FUNCTIONALTESTFACTORY_H
