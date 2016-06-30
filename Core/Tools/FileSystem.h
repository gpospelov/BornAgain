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

    //! Sets relative path from working directory to executable module.
    //! The value is known only from argv[0] and should be set from outside
    static void SetArgvPath(const std::string& argv0);
    static std::string GetArgvPath();

    //! Returns file extension
    static std::string GetFileExtension(const std::string& name);

    //! returns path to executable
    static std::string GetPathToExecutable(const std::string& argv0=GetArgvPath());

    //! returns absolute path to data taking into acount location of executable
    static std::string GetPathToData(
        const std::string& rel_data_path, const std::string& argv0=GetArgvPath());

    //! creates directory in current directory
    static bool CreateDirectory(const std::string& dir_name);

    //! join paths together
    static std::string GetJoinPath(const std::string& spath1, const std::string& spath2);

private:
    //! value of argv[0], i.e. the path from working directory to executable module
    //! including the name of executable module
    static std::string m_argv0_path;
    static std::string m_reference_data_dir;
};

}

#endif // FILESYSTEM_H
