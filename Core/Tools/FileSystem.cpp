// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/FileSystem.cpp
//! @brief     Implements class FileSystem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FileSystem.h"
#include "Exceptions.h"
#include <boost/filesystem.hpp>
#include <cassert>
#include <glob.h>

//! Returns path to the current (working) directory.

std::string Utils::FileSystem::GetWorkingPath()
{
    return boost::filesystem::current_path().string();
}

//! Returns path to BornAgain home directory.

std::string Utils::FileSystem::GetHomePath()
{
    throw Exceptions::NotImplementedException(
        "Utils::FileSystem::GetHomePath()-> Not implemented anymore...");
}

//! Returns file extension.

std::string Utils::FileSystem::GetFileExtension(const std::string& name)
{
    return boost::filesystem::extension(name.c_str());
}


bool Utils::FileSystem::CreateDirectory(const std::string &dir_name)
{
    assert(dir_name!="");
    return boost::filesystem::create_directory(dir_name);
}

std::string Utils::FileSystem::GetJoinPath(const std::string &spath1, const std::string &spath2)
{
    assert(spath1!="");
    assert(spath2!="");
    boost::filesystem::path path1(spath1);
    boost::filesystem::path path2(spath2);
    boost::filesystem::path full_path = path1 / path2;

    return full_path.string();
}

//! Returns file names that agree with glob pattern.
std::vector<std::string> Utils::FileSystem::glob(const std::string& pattern)
{
    glob_t glob_result;
    ::glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
    std::vector<std::string> ret;
    for(unsigned int i=0; i<glob_result.gl_pathc; ++i)
        ret.push_back(std::string(glob_result.gl_pathv[i]));
    globfree(&glob_result);
    return ret;
}
