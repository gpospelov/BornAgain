//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/mainwindow/styleutils.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/mainwindow/styleutils.h"
#include "gui2/resources/resources.h"
#include <QFontMetrics>
#include <QSize>
#include <QToolBar>
#include <QWidget>

namespace gui2 {

QSize StyleUtils::ToolBarIconSize()
{
    return QSize(24, 24);
}

QSize StyleUtils::DockSizeHint()
{
    return QSize(480, 360);
}

QSize StyleUtils::DockMinimumSizeHint()
{
    return QSize(320, 240);
}

void StyleUtils::SetToolBarStyleTextBesides(QToolBar* toolbar)
{
    InitIconResources();
    toolbar->setIconSize(StyleUtils::ToolBarIconSize());
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

} // namespace gui2
