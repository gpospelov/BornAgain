// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/gui_functional_test.h
//! @brief     Defines function to run all core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUI_FUNCTIONAL_TESTS_H
#define GUI_FUNCTIONAL_TESTS_H

#include "WinDllMacros.h"
#include <string>

//! run GUI functional tests with given name
BA_CORE_API_ int GUI_FUNCTIONAL_TEST(const std::string &test_name);

#endif
