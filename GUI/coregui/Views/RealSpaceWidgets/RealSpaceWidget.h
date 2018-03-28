// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.h
//! @brief     Defines class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACEWIDGET_H
#define REALSPACEWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

#include <QTreeView>

class RealSpaceToolBar;
class RealSpaceCanvas;
class RealSpaceActions;
class RealSpacePanel;
class SampleModel;

//! Prototype of real space widget to present sample structure in 3D view.

class BA_CORE_API_ RealSpaceWidget : public QWidget
{
    Q_OBJECT

public:
    RealSpaceWidget(SampleModel* sampleModel, QTreeView* treeView, QWidget* parent = nullptr);

    void setModel(SampleModel* model, QTreeView* treeView);

private:
    RealSpaceActions* m_actions;
    RealSpaceToolBar* m_toolBar;
    RealSpaceCanvas* m_canvas;
    RealSpacePanel* m_panel;
};

#endif // REALSPACEWIDGET_H
