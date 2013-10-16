// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/Utils.cpp
//! @brief     Implements various stuff in namespace Utils.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Utils.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#ifdef DEBUG_FPE
#include <fenv.h>
#ifdef Q_OS_MAC
#include "fp_exception_glibc_extension.h"
#endif
#endif


std::string Utils::FileSystem::m_argv0_path = std::string();

//! Parse double values from string to vector of double

vdouble1d_t Utils::String::parse_doubles(const std::string& str)
{
    vdouble1d_t buff_1d;
    std::istringstream iss(str);
    std::copy(std::istream_iterator<double>(iss),
              std::istream_iterator<double>(), back_inserter(buff_1d));
    if( buff_1d.empty() ) {
        std::cout << "OutputDataReadFileASCII::parse_doubles() -> "
            "Warning! No parsed values in 1d vector of doubles." << std::endl;
    }
    return buff_1d;
}

//! Round double numbers in string to given precision.

//! If precision is 6, then 7.2908527770e+03 -> 7.290853e+03.
//! This method is used to compare IsGisaxs and our ASCII files
//! at equal precision.
//!
std::string Utils::String::round_doubles(const std::string& str, int precision)
{
    std::string newline;
    std::istringstream is0(str.c_str());
    double number;
    while( is0 >> number ) {
        std::ostringstream os;
        os << std::scientific << std::setprecision(precision) << number;
        newline += os.str() + std::string("    ");
    }
    return newline;
}

//! Returns true if text matches pattern with wildcards '*' and '?'.

bool Utils::String::MatchPattern(
    const std::string& text, std::string wildcardPattern)
{
    bool caseSensitive = false;

    // escape all regex special characters, except '?' and '*'
    boost::replace_all(wildcardPattern, "\\", "\\\\");
    boost::replace_all(wildcardPattern, "^", "\\^");
    boost::replace_all(wildcardPattern, ".", "\\.");
    boost::replace_all(wildcardPattern, "$", "\\$");
    boost::replace_all(wildcardPattern, "|", "\\|");
    boost::replace_all(wildcardPattern, "(", "\\(");
    boost::replace_all(wildcardPattern, ")", "\\)");
    boost::replace_all(wildcardPattern, "[", "\\[");
    boost::replace_all(wildcardPattern, "]", "\\]");
    boost::replace_all(wildcardPattern, "+", "\\+");
    boost::replace_all(wildcardPattern, "/", "\\/");

    // Convert chars '*?' to their regex equivalents
    boost::replace_all(wildcardPattern, "?", ".");
    boost::replace_all(wildcardPattern, "*", ".*");

    // constructing regexp pattern
    wildcardPattern = "^" + wildcardPattern + "$";
    boost::regex pattern(wildcardPattern, caseSensitive ? boost::regex::normal : boost::regex::icase);

    // applaying match
    return boost::regex_match(text, pattern);
}

//! Split string into vector of string using delimeter.

std::vector<std::string> Utils::String::Split(
    const std::string& text, const std::string& delimeter)
{
    std::vector<std::string> tokens;
    boost::split(tokens, text, boost::is_any_of(delimeter));
    return tokens;
}


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


//! enables exception throw in the case of NaN, Inf
void Utils::EnableFloatingPointExceptions()
{
#ifdef DEBUG_FPE
#ifndef _WIN32
    std::cout << "Utils::EnableFloatingPointExceptions()  -> Enabling floating point exception debugging"
              << std::endl;
    feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
//    feenableexcept(-1);
#endif // _WIN32
#else
    std::cout << "Utils::EnableFloatingPointExceptions()  -> Can't enable floating point exceptions. Available in debug mode only."
              << std::endl;
#endif
}
