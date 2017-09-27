// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SysUtils.h
//! @brief     Defines various stuff in namespace Utils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SYSUTILS_H
#define SYSUTILS_H

#include "WinDllMacros.h"
#include "StringUtils.h"
#include <string>

//! Utility functions getCurrentDateAndTime, enableFloatingPointExceptions.

namespace SysUtils {

    BA_CORE_API_ std::string getCurrentDateAndTime();

    //! Enables exception throw in the case of NaN, Inf.
    BA_CORE_API_ void enableFloatingPointExceptions();

    //! Enables exception throw in the case of NaN, Inf.
    BA_CORE_API_ void enableFloatingPointExceptions();

    //! Returns    environment variable
    BA_CORE_API_ std::string getenv(const std::string& name);
} // namespace SysUtils

#endif // SYSUTILS_H
