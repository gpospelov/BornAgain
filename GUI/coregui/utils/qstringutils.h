// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/qstringutils.h
//! @brief     Defines functions from Utils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef QSTRINGUTILS_H
#define QSTRINGUTILS_H

#include "WinDllMacros.h"
#include <QString>

namespace GUI_StringUtils
{

BA_CORE_API_ QString withTildeHomePath(const QString& path);

}

#endif // QSTRINGUTILS_H
