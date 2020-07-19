// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/GUISpecialTestFactory.h
//! @brief     Defines GUISpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISPECIAL_GUISPECIALTESTFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISPECIAL_GUISPECIALTESTFACTORY_H

#include "Fit/TestEngine/IFactory.h"
#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! @class GUISpecialTestFactory
//! @brief Collection of special tests for GUI library.

class GUISpecialTestFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    GUISpecialTestFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISPECIAL_GUISPECIALTESTFACTORY_H
