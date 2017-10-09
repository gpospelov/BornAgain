// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/FunctionalTestFactory.h
//! @brief     Defines FunctionalTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTFACTORY_H
#define FUNCTIONALTESTFACTORY_H

#include "IFactory.h"
#include "IFunctionalTest.h"

//! Simple factory to hold packs of functional tests.

class BA_CORE_API_ FunctionalTestFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    std::unique_ptr<IFunctionalTest> createTest(std::string& test_name);
};

#endif

