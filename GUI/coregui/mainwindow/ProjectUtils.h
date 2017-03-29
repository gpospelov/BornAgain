// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/ProjectUtils.h
//! @brief     Defines ProjectUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROJECTUTILS_H
#define PROJECTUTILS_H

#include "WinDllMacros.h"
#include <QString>

//! Defines convenience function for project manager and document.

namespace ProjectUtils
{

//! Returns project name deduced from project file name.
BA_CORE_API_ QString projectName(const QString& projectFileName);

//! Returns project directory deduced from project file name.
BA_CORE_API_ QString projectDir(const QString& projectFileName);

}

#endif // PROJECTUTILS_H
