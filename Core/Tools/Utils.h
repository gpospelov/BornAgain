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
#include "StringUtils.h"
#include <string>
#include <vector>

namespace Utils {

class BA_CORE_API_ System
{
public:
    static int getThreadHardwareConcurrency();
    static std::string getCurrentDateAndTime();
};

//! enables exception throw in the case of NaN, Inf
BA_CORE_API_ void EnableFloatingPointExceptions();

//! Returns shape nrows, ncols of 2D array (for numpy)
BA_CORE_API_ std::pair<size_t, size_t> getShape(const std::vector<std::vector<double>>& data);

} // namespace Utils

#endif // UTILS_H
