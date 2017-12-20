// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/IntensityDataItemUtils.h
//! @brief     Defines namespace IntensityDataItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTENSITYDATAITEMUTILS_H
#define INTENSITYDATAITEMUTILS_H

#include "WinDllMacros.h"

class IntensityDataItem;
class SessionItem;

//! Utility functions for IntensityDataItem

namespace IntensityDataItemUtils
{

//! Returns IntensityDataItem contained as a child in givent parent.
BA_CORE_API_ IntensityDataItem* intensityDataItem(SessionItem* parent);

}

#endif  //  INTENSITYDATAITEMUTILS_H
