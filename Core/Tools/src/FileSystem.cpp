#include "FileSystem.h"
#include "BAConfigure.h"
#include "Exceptions.h"
#include <boost/filesystem.hpp>


std::string Utils::FileSystem::m_argv0_path = std::string();

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
    return std::string();
}

std::string Utils::FileSystem::GetPathToExecutable(const std::string& argv0)
{
    std::string result = boost::filesystem::canonical( argv0.c_str() ).parent_path().string();
    return result;
}


std::string Utils::FileSystem::GetPathToData(const std::string& rel_data_path, const std::string& argv0)
{
//#ifdef _WIN32
//    // windows build place executable in additional sub-directory 'release'
//    std::string result = (boost::filesystem::canonical( argv0.c_str() ).parent_path() / boost::filesystem::path("../") / boost::filesystem::path(rel_data_path)).string();
//#else
    std::string result = (boost::filesystem::canonical( argv0.c_str() ).parent_path() / boost::filesystem::path(rel_data_path)).string();
//#endif
    return result;
}

//! Returns file extension.

std::string Utils::FileSystem::GetFileExtension(const std::string& name)
{
    return boost::filesystem::extension(name.c_str());
}

//! Does name contain *.gz extension?

bool Utils::FileSystem::isGZipped(const std::string& name)
{
    static const std::string gzip_extension(".gz");
    if ( Utils::FileSystem::GetFileExtension(name) == gzip_extension)
        return true;
    return false;
}

//! Returns file main extension (without .gz).

std::string Utils::FileSystem::GetFileMainExtension(const std::string& name)
{
    if( !isGZipped(name) ) {
        return Utils::FileSystem::GetFileExtension(name);
    } else {
        std::string stripped_name = name.substr(0, name.size()-3);
        return Utils::FileSystem::GetFileExtension(stripped_name);
    }
}


std::string Utils::FileSystem::GetSourceDir()
{
#ifdef BORNAGAIN_SOURCE_DIR
    return std::string(BORNAGAIN_SOURCE_DIR );
#else
    throw LogicErrorException("Utils::FileSystem::GetSourceDir() -> Error. Not configured.");
#endif
}

std::string Utils::FileSystem::GetInstallDir()
{
#ifdef BORNAGAIN_INSTALL_DIR
    return std::string(BORNAGAIN_INSTALL_DIR);
#else
    throw LogicErrorException("Utils::FileSystem::GetInstallDir() -> Error. Not configured.");
#endif
}

std::string Utils::FileSystem::GetReferenceDataDir()
{
    return GetSourceDir() + std::string("/Tests/ReferenceData/BornAgain/");
}


