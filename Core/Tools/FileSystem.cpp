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

std::string Utils::FileSystem::m_argv0_path = std::string();
std::string Utils::FileSystem::m_reference_data_dir = std::string();

void Utils::FileSystem::SetArgvPath(const std::string& argv0)
{
    m_argv0_path = argv0;
}

std::string Utils::FileSystem::GetArgvPath()
{
    return m_argv0_path;
}


//! Returns path to the current (working) directory.

std::string Utils::FileSystem::GetWorkingPath()
{
    return boost::filesystem::current_path().string();
}

//! Returns path to BornAgain home directory.

std::string Utils::FileSystem::GetHomePath()
{
    throw NotImplementedException("Utils::FileSystem::GetHomePath()-> Not implemented anymore...");
}

std::string Utils::FileSystem::GetPathToExecutable(const std::string& argv0)
{
    std::string result = boost::filesystem::canonical( argv0.c_str() ).parent_path().string();
    return result;
}


std::string Utils::FileSystem::GetPathToData(
    const std::string& rel_data_path, const std::string& argv0)
{
    std::string result = (boost::filesystem::canonical( argv0.c_str() ).parent_path() /
                          boost::filesystem::path(rel_data_path)).string();
    return result;
}

//! Returns file extension.

std::string Utils::FileSystem::GetFileExtension(const std::string& name)
{
    return boost::filesystem::extension(name.c_str());
}


bool Utils::FileSystem::CreateDirectory(const std::string &dir_name)
{
    boost::filesystem::path dir(dir_name);
    return boost::filesystem::create_directory(dir);
}

std::string Utils::FileSystem::GetJoinPath(const std::string &spath1, const std::string &spath2)
{
    boost::filesystem::path path1(spath1);
    boost::filesystem::path path2(spath2);
    boost::filesystem::path full_path = path1 / path2;

    return full_path.string();
}
