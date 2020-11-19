//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/StringUtils.cpp
//! @brief     Implements a few helper functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Tools/StringUtils.h"
#include <boost/algorithm/string.hpp>
#include <regex>

namespace mumufit
{

//! Returns true if text matches pattern with wildcards '*' and '?'.
bool StringUtils::matchesPattern(const std::string& text, const std::string& wildcardPattern)
{
    // escape all regex special characters, except '?' and '*'
    std::string mywildcardPattern = wildcardPattern;
    boost::replace_all(mywildcardPattern, "\\", "\\\\");
    boost::replace_all(mywildcardPattern, "^", "\\^");
    boost::replace_all(mywildcardPattern, ".", "\\.");
    boost::replace_all(mywildcardPattern, "$", "\\$");
    boost::replace_all(mywildcardPattern, "|", "\\|");
    boost::replace_all(mywildcardPattern, "(", "\\(");
    boost::replace_all(mywildcardPattern, ")", "\\)");
    boost::replace_all(mywildcardPattern, "[", "\\[");
    boost::replace_all(mywildcardPattern, "]", "\\]");
    boost::replace_all(mywildcardPattern, "+", "\\+");
    boost::replace_all(mywildcardPattern, "/", "\\/");

    // Convert chars '*?' to their regex equivalents
    boost::replace_all(mywildcardPattern, "?", ".");
    boost::replace_all(mywildcardPattern, "*", ".*");

    // constructing regexp pattern
    mywildcardPattern = "^" + mywildcardPattern + "$";
    std::regex pattern(mywildcardPattern);

    // applaying match
    return std::regex_match(text, pattern);
}

//! Returns token vector obtained by splitting string at delimiters.
std::vector<std::string> StringUtils::split(const std::string& text, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    boost::split(tokens, text, boost::is_any_of(delimiter));
    return tokens;
}

std::string StringUtils::removeSubstring(const std::string& text, const std::string& substr)
{
    std::string result = text;
    for (std::string::size_type i = result.find(substr); i != std::string::npos;
         i = result.find(substr))
        result.erase(i, substr.length());
    return result;
}

std::string StringUtils::to_lower(std::string text)
{
    boost::to_lower(text);
    return text;
}

} // namespace mumufit
