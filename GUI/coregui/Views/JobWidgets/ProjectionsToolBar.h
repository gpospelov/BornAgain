// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsToolBar.h
//! @brief     Defines class ProjectionsToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSTOOLBAR_H
#define PROJECTIONSTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class ProjectionsEditorActions;

//! Toolbar with projections buttons (horizontal projections, vertical projections, select, zoom)
//! located at the right-hand side of ProjectionsEditor (part of JobProjectionsWidget).

class ProjectionsToolBar : public QToolBar
{
    Q_OBJECT

public:
    ProjectionsToolBar(ProjectionsEditorActions* editorActions, QWidget* parent = 0);

private:
    ProjectionsEditorActions* m_editorActions;
};


#endif // PROJECTIONSTOOLBAR_H
