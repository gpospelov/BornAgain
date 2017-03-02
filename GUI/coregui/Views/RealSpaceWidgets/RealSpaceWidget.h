// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.h
//! @brief     Defines class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACEWIDGET_H
#define REALSPACEWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class RealSpaceToolBar;
class RealSpaceView;
class RealSpaceScene;
class RealSpaceActions;
class RealSpacePanel;
class SampleModel;

//! Prototype of real space widget to present sample structure in 3D view.

class BA_CORE_API_ RealSpaceWidget : public QWidget
{
    Q_OBJECT

public:
    RealSpaceWidget(QWidget* parent = 0);

    void setModel(SampleModel* model);

private:
    RealSpaceToolBar* m_toolBar;
    RealSpaceView* m_view;
    RealSpaceScene* m_scene;
    RealSpaceActions* m_actions;
    RealSpacePanel* m_panel;
};

#endif // REALSPACEWIDGET_H
