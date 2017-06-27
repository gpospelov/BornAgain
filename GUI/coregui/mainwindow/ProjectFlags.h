// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/ProjectFlags.h
//! @brief     Defines class ProjectFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROJECTFLAGS_H
#define PROJECTFLAGS_H

#include "WinDllMacros.h"
#include <QFlags>

class BA_CORE_API_ ProjectFlags
{
public:
    enum EDocumentStatus
    {
        STATUS_OK = 0x0001,
        STATUS_WARNING = 0x0002,
        STATUS_FAILED = 0x0004,
    };

    Q_DECLARE_FLAGS(DocumentStatus, EDocumentStatus)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ProjectFlags::DocumentStatus)

#endif //  PROJECTFLAGS_H
