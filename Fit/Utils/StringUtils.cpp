// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/StringUtils.cpp
//! @brief     Implements a few helper functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StringUtils.h"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

//! Returns true if text matches pattern with wildcards '*' and '?'.

bool StringUtils::matchesPattern(const std::string& text, const std::string& wildcardPattern)
{
    bool caseSensitive(true);

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
    boost::regex pattern(mywildcardPattern,
                         caseSensitive ? boost::regex::normal : boost::regex::icase);

    // applaying match
    return boost::regex_match(text, pattern);
}

//! Returns string right-padded with blanks.

std::string StringUtils::padRight(const std::string& name, int length)
{
    std::string result = name;
    result.resize(length,' ');
    return result;
}
