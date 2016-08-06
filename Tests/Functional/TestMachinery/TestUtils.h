// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.h
//! @brief     Declares various stuff in namespace TestUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

namespace TestUtils {

//! Returns file names that agree with glob pattern.
std::vector<std::string> glob(const std::string& pattern);

} // namespace TestUtils

#endif // TESTUTILS_H
