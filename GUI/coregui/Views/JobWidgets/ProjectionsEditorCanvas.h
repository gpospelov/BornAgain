// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorCanvas.h
//! @brief     Defines class ProjectionsEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSEDITORCANVAS_H
#define PROJECTIONSEDITORCANVAS_H

#include "WinDllMacros.h"
#include <QWidget>

//! Holds a graphics scene to draw projections on top of ColorMap. Being a part
//! of ProjectionEditor, provides interaction logic between graphics scene and ProjectionsWidget.

class ProjectionsEditorCanvas : public QWidget
{
    Q_OBJECT

public:
    ProjectionsEditorCanvas(QWidget *parent = 0);

};


#endif // PROJECTIONSEDITORCANVAS_H
