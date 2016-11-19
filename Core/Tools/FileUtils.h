// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/FileUtils.h
//! @brief     Defines namespace FileUtils.
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

//! Utility functions to deal with file system.

namespace FileUtils {

    //! Returns extension of given filename.
    BA_CORE_API_ std::string extension(const std::string& fname);

    //! Creates directory in current directory
    BA_CORE_API_ bool createDirectory(const std::string& dir_name);

    //! Returns filenames of files in directory
    BA_CORE_API_ std::vector<std::string> filesInDirectory(const std::string& dir_name);

    //! Returns joint path name.
    BA_CORE_API_ std::string jointPath(const std::string& spath1, const std::string& spath2);

    //! Returns path without directory part ("Foo/Bar/Doz.int.gz" -> "Doz.int.gz")
    BA_CORE_API_ std::string filename(const std::string& path);

    //! Returns file names that agree with a regex glob pattern.
    BA_CORE_API_ std::vector<std::string> glob(
        const std::string& dir, const std::string& pattern);

} // namespace FileUtils

#endif // FILESYSTEM_H
