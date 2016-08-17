// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/FileSystem.h
//! @brief     Defines class FileSystem
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

namespace FileSystem {

    //! Returns file extension
    std::string GetFileExtension(const std::string& name);

    //! creates directory in current directory
    bool CreateDirectory(const std::string& dir_name);

    //! join paths together
    std::string GetJoinPath(const std::string& spath1, const std::string& spath2);

    //! Returns path without directory part ("Foo/Bar/Doz.int.gz" -> "Doz.int.gz")
    std::string filename(const std::string& path);

    //! Returns file names that agree with glob pattern.
    std::vector<std::string> glob(const std::string& pattern);

} // namespace FileSystem

#endif // FILESYSTEM_H
