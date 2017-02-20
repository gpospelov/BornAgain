// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsToolBar.cpp
//! @brief     Implements class ProjectionsToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsToolBar.h"
#include "mainwindow_constants.h"

ProjectionsToolBar::ProjectionsToolBar(ProjectionsEditorActions* editorActions, QWidget* parent)
    : QToolBar(parent)
    , m_editorActions(editorActions)
{
    setIconSize(QSize(Constants::toolbar_icon_size, Constants::toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

}
