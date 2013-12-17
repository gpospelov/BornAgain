// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/FileSystem.h
//! @brief     Defines class FileSystem
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "WinDllMacros.h"
#include <string>

//! Utilities to deal with file system.

namespace Utils {

class BA_CORE_API_ FileSystem
{
public:
    //! Returns path to the current (working) directory
    static std::string GetWorkingPath();

    //! Returns path to BornAgain home directory
    static std::string GetHomePath();

    //! Sets relative path, which is the path from working directory to executable module. The value is known only from argv[0] and should be set from outside
    static void SetArgvPath(const std::string& argv0);
    static std::string GetArgvPath();

    //! Returns file extension
    static std::string GetFileExtension(const std::string& name);

    //! Returns true if name contains *.gz extension
    static bool isGZipped(const std::string& name);

    //! Returns file extension after stripping '.gz' if any
    static std::string GetFileMainExtension(const std::string& name);

    //! returns path to executable
    static std::string GetPathToExecutable(const std::string& argv0=GetArgvPath());

    //! returns absolute path to data taking into acount location of executable
    static std::string GetPathToData(const std::string& rel_data_path, const std::string& argv0=GetArgvPath());

    //! return path to the code source directory
    static std::string GetSourceDir();

    //! return path to the install directory
    static std::string GetInstallDir();

    //! return path to the reference data
    static std::string GetReferenceDataDir();
    static void SetReferenceDataDir(const std::string &path) {m_reference_data_dir = path; }

private:
    static std::string m_argv0_path; //!< it's value of argv[0], i.e. the path from working directory to executable module including the name of executable module
    static std::string m_reference_data_dir;
};

}


#endif
