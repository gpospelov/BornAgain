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
#include <QModelIndex>
#include <memory>

class RealSpaceToolBar;
class RealSpaceView;
class RealSpaceCanvas;
class RealSpaceActions;
class RealSpacePanel;
class SampleModel;
class RealSpaceModel;

//! Prototype of real space widget to present sample structure in 3D view.

class BA_CORE_API_ RealSpaceWidget : public QWidget
{
    Q_OBJECT

public:
    RealSpaceWidget(QWidget* parent = 0);
    ~RealSpaceWidget();

    void setModel(SampleModel* model);

public slots:
    void onSelectionChanged(const QModelIndex& selected);

private slots:
    void updateScene();
    void resetScene();

private:
    void setConnected(SampleModel* model, bool makeConnected);

    RealSpaceToolBar* m_toolBar;
    RealSpaceView* m_view;
    RealSpaceCanvas* m_scene;
    RealSpaceActions* m_actions;
    RealSpacePanel* m_panel;

    SampleModel* m_sampleModel;
    QModelIndex m_currentSelection;

    std::unique_ptr<RealSpaceModel> m_realSpaceModel;
};

#endif // REALSPACEWIDGET_H
