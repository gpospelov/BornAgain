// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/CoreSpecialTestFactory.h
//! @brief     Defines CoreSpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_CORESPECIALTESTFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_CORESPECIALTESTFACTORY_H

#include "Tests/Functional/TestMachinery/FunctionalTestFactory.h"

//! @class CoreSpecialTestFactory
//! @brief Collection of special case for Core library.

class CoreSpecialTestFactory : public FunctionalTestFactory
{
public:
    CoreSpecialTestFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_CORESPECIALTESTFACTORY_H
