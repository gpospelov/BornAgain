// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/StringUtils.h
//! @brief     Declares a few helper functions
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

namespace StringUtils {

    //! Returns true if text matches pattern with wildcards '*' and '?'.
    BA_CORE_API_ bool matchesPattern(const std::string& text, const std::string& wildcardPattern);

    BA_CORE_API_ std::string padRight(const std::string& name, int length);

} // namespace StringUtils

#endif // STRINGUTILS_H
