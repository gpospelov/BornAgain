// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.cpp
//! @brief     Implements various stuff in namespace TestUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestUtils.h"
#include <string>
#include <vector>
#include <glob.h>

//! Returns file names that agree with glob pattern.
std::vector<std::string> TestUtils::glob(const std::string& pattern)
{
    glob_t glob_result;
    glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
    std::vector<std::string> ret;
    for(unsigned int i=0; i<glob_result.gl_pathc; ++i)
        ret.push_back(std::string(glob_result.gl_pathv[i]));
    globfree(&glob_result);
    return ret;
}
