// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/pyscript_functional_test.h
//! @brief     Declares function to run all pyscript functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSCRIPT_FUNCTIONAL_TESTS_H
#define PYSCRIPT_FUNCTIONAL_TESTS_H

#include "WinDllMacros.h"
#include <string>

//! run pyscript functional tests with given name
BA_CORE_API_ int PYSCRIPT_FUNCTIONAL_TEST(const std::string &test_name);

#endif
