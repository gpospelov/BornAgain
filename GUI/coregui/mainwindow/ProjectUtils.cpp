// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/ProjectUtils.cpp
//! @brief     Implements ProjectUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProjectUtils.h"
#include <QFileInfo>

QString ProjectUtils::projectName(const QString& projectFileName)
{
    QFileInfo info(projectFileName);
    return info.baseName();
}

QString ProjectUtils::projectDir(const QString& projectFileName)
{
    QFileInfo info(projectFileName);
    return info.path();
}
