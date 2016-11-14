// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/StringUtils.h
//! @brief     Defines a few helper functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

namespace Utils {

namespace String {

//! Returns true if text matches pattern with wildcards '*' and '?'.
BA_CORE_API_ bool matchesPattern(const std::string& text, const std::string& wildcardPattern);

BA_CORE_API_ std::string padRight(const std::string& name, int length);

//! Split string into vector of string using delimeter.
BA_CORE_API_ std::vector<std::string> split(const std::string& text, const std::string& delimeter);

//! replace all occurences of items from string text with delimeter
BA_CORE_API_ void replaceItemsFromString(std::string& text, const std::vector<std::string>& items,
                                         const std::string& replacement=std::string(""));

//! Returns string obtain by joining vector elements
BA_CORE_API_ std::string join(const std::vector<std::string>& joinable, const std::string& joint);

//! Removes multiple occurences of given substring from a string and returns result.
BA_CORE_API_ std::string removeSubstring(const std::string& text, const std::string& substr);
}
}

#endif // STRINGUTILS_H
