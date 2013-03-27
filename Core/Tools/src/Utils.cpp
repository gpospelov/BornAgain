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
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <iomanip>
#include <boost/algorithm/string.hpp>

std::string Utils::FileSystem::m_relative_path = "relative path is undefined";

//! Parse double values from string to vector of double

vdouble1d_t Utils::String::parse_doubles(const std::string &str)
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
std::string Utils::String::round_doubles(const std::string &str, int precision)
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
    const std::string &text, std::string wildcardPattern)
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
    const std::string &text, const std::string &delimeter)
{
    std::vector<std::string> tokens;
    boost::split(tokens, text, boost::is_any_of(delimeter));
    return tokens;
}

//! Returns path to the current (working) directory.

std::string Utils::FileSystem::GetWorkingPath()
{
    return boost::filesystem::current_path().string();
}

//! Returns path to BornAgain home directory.

std::string Utils::FileSystem::GetHomePath()
{
    // the path to executable module is: boost::filesystem::current_path() + argv[0]
    // we expect that variable m_relative_path (aka argv[0]) has been set from outside
    // and use boost::filesystem::system_complete() to get complete path to executable

    //std::string path = boost::filesystem::system_complete(m_relative_path.c_str()).string(); // without resolving symlinks
    //std::string path = boost::filesystem::canonical( m_relative_path.c_str() ).string(); // with automatic resolving of symlinks, boost>= 1.48

    // for boost 1.46 lets use another way
    std::string path;
    if( boost::filesystem::is_symlink(m_relative_path.c_str()) ) {
        path = boost::filesystem::read_symlink( m_relative_path.c_str() ).string();
    } else {
        path = boost::filesystem::system_complete(m_relative_path.c_str()).string();
    }

    // at this point the value should be something like '/Users/jamesbond/development/git/./BornAgain/App/App'
    //std::cout << "Utils::FileSystem::GetHomePath() -> path '" << path << "'" << std::endl;

    // lets strip everything after 'BornAgain' to get path to project home directory    
    std::string project_name("BornAgain");
    std::string::size_type pos = path.rfind(project_name);
    if(pos == std::string::npos) {
        throw LogicErrorException(
            "Utils::FileSystem::GetHomePath() -> "
            "Error. Cant parse path to application from line '"+path+"'");
    }
    path.erase(pos+project_name.size());
    path += "/";
    return path;
}

//! Returns file extension.

std::string Utils::FileSystem::GetFileExtension(const std::string &name)
{
    return boost::filesystem::extension(name.c_str());
}

//! Does name contain *.gz extension?

bool Utils::FileSystem::isGZipped(const std::string &name)
{
    static const std::string gzip_extension(".gz");
    if ( Utils::FileSystem::GetFileExtension(name) == gzip_extension)
        return true;
    return false;
}

//! Returns file main extension (without .gz).

std::string Utils::FileSystem::GetFileMainExtension(const std::string &name)
{
    if( !isGZipped(name) ) {
        return Utils::FileSystem::GetFileExtension(name);
    } else {
        std::string stripped_name = name.substr(0, name.size()-3);
        return Utils::FileSystem::GetFileExtension(stripped_name);
    }
}
