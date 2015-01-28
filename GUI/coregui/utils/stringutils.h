// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/stringutils.h
//! @brief     Defines functions from Utils namespace
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "WinDllMacros.h"
#include <QString>

namespace Utils
{


BA_CORE_API_ QString withTildeHomePath(const QString &path);


}


#endif

