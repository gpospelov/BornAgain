// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/FileSystem.h
//! @brief     Declares class FileSystem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

//! Utilities to deal with file system.

namespace Utils {

//! @class FileSystem
//! @ingroup tools_internal
//! @brief Class collecting utilities to work with file system.

class BA_CORE_API_ FileSystem
{
public:
    //! Returns path to the current (working) directory
    static std::string GetWorkingPath();

    //! Returns path to BornAgain home directory
    static std::string GetHomePath();

    //! Returns file extension
    static std::string GetFileExtension(const std::string& name);

    //! creates directory in current directory
    static bool CreateDirectory(const std::string& dir_name);

    //! join paths together
    static std::string GetJoinPath(const std::string& spath1, const std::string& spath2);

    //! Returns file names that agree with glob pattern.
    static std::vector<std::string> glob(const std::string& pattern);
};

}

#endif // FILESYSTEM_H
