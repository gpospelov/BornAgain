// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Utils.h
//! @brief     Defines various stuff in namespace Utils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef UTILS_H
#define UTILS_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

namespace Utils {

//! Collection of utilities for std::string.
//! @ingroup tools_internal

class BA_CORE_API_ String
{
public:
    //! Split string into vector of string using delimeter.
    static std::vector<std::string> split(const std::string& text, const std::string& delimeter);

    //! replace all occurences of items from string text with delimeter
    static void replaceItemsFromString(std::string& text, const std::vector<std::string>& items,
                                       const std::string& replacement=std::string(""));

    //! Returns string obtain by joining vector elements
    static std::string join(const std::vector<std::string>& joinable, const std::string& joint);
};


class BA_CORE_API_ System
{
public:
    static int getThreadHardwareConcurrency();
    static std::string getCurrentDateAndTime();
};

//! enables exception throw in the case of NaN, Inf
BA_CORE_API_ void EnableFloatingPointExceptions();

} // namespace Utils

#endif // UTILS_H
