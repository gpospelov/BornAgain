#include "Utils.h"
#include "Exceptions.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>

std::string Utils::FileSystem::m_relative_path = "in the middle of nowhere";


//! return true if text matches wildcards
bool Utils::StringMatchText::WildcardPattern(const std::string &text, std::string wildcardPattern)
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


//! return path to the current (working) directory
std::string Utils::FileSystem::GetWorkingPath()
{
    return boost::filesystem::current_path().string();
}


//! return path to GISASFW home directory
std::string Utils::FileSystem::GetHomePath()
{
    // the path to executable module is: boost::filesystem::current_path() + argv[0]
    // we expect that variable m_relative_path (aka argv[0]) has been set from outside
    // and use boost::filesystem::system_complete() to get complete path to executable

    std::string path = boost::filesystem::system_complete(m_relative_path.c_str()).string();
    // at this point the value should be something like '/Users/jamesbond/development/git/./GISASFW/App/App'

    // lets strip everything after 'GISASFW' to get path to project home directory
    std::string project_name("GISASFW");
    std::string::size_type pos = path.find_first_of(project_name);
    if(pos == std::string::npos) {
        throw LogicErrorException("Utils::FileSystem::GetHomePath() -> Error. Cant parse path to application from line '"+path+"'");
    }
    path.erase(pos+project_name.size());
    path += "/";
    return path;
}

