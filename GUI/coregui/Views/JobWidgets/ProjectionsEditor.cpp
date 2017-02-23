// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditor.cpp
//! @brief     Implements class ProjectionsEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsEditor.h"
#include "ProjectionsEditorActions.h"
#include "ProjectionsToolBar.h"
#include "ProjectionsWidget.h"
#include "ProjectionsPropertyPanel.h"
#include "ProjectionsEditorCanvas.h"
#include "minisplitter.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "MaskEditorFlags.h"
#include "MaskGraphicsScene.h"
#include <QItemSelectionModel>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>

ProjectionsEditor::ProjectionsEditor(QWidget* parent)
    : QMainWindow(parent)
    , m_editorActions(new ProjectionsEditorActions(this))
    , m_toolBar(new ProjectionsToolBar(m_editorActions))
    , m_projectionsCanvas(new ProjectionsEditorCanvas)
    , m_projectionsWidget(new ProjectionsWidget)
    , m_propertyPanel(new ProjectionsPropertyPanel)
    , m_selectionModel(nullptr)
    , m_rightSplitter(new Manhattan::MiniSplitter)
    , m_bottomSplitter(new QSplitter)
{
    addToolBar(Qt::RightToolBarArea, m_toolBar);

    m_bottomSplitter->setOrientation(Qt::Vertical);
    m_bottomSplitter->addWidget(m_projectionsCanvas);
    m_bottomSplitter->addWidget(m_projectionsWidget);
    m_bottomSplitter->setStyleSheet("background-color:white;");

    m_rightSplitter->addWidget(m_bottomSplitter);
    m_rightSplitter->addWidget(m_propertyPanel);

    setCentralWidget(m_rightSplitter);

    m_propertyPanel->setHidden(true);
    setup_connections();
}

void ProjectionsEditor::setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                                   IntensityDataItem* intensityItem)
{
    Q_UNUSED(model);
    Q_UNUSED(shapeContainerIndex);

    delete m_selectionModel;
    m_selectionModel = new QItemSelectionModel(model, this);

    m_propertyPanel->setItem(intensityItem);
    m_projectionsCanvas->setContext(model, shapeContainerIndex, intensityItem);
    m_projectionsCanvas->setSelectionModel(m_selectionModel);
    m_projectionsWidget->setItem(intensityItem);

    m_editorActions->setModel(model, shapeContainerIndex);
    m_editorActions->setSelectionModel(m_selectionModel);
}

QList<QAction*> ProjectionsEditor::topToolBarActions()
{
    return m_editorActions->topToolBarActions();
}

void ProjectionsEditor::setup_connections()
{
    // tool panel request is propagated from editorActions to this MaskEditor
    connect(m_editorActions, SIGNAL(resetViewRequest()),
            m_projectionsCanvas, SLOT(onResetViewRequest()));

    // tool panel request is propagated from editorActions to this MaskEditor
    connect(m_editorActions, &ProjectionsEditorActions::propertyPanelRequest,
            [=](){m_propertyPanel->setHidden(!m_propertyPanel->isHidden());});

    // selection/drawing activity is propagated from ToolBar to graphics scene
    connect(m_toolBar, SIGNAL(activityModeChanged(MaskEditorFlags::Activity)),
            m_projectionsCanvas, SLOT(onActivityModeChanged(MaskEditorFlags::Activity)));

    // Delete request is propagated from canvas to actions
    connect(m_projectionsCanvas, SIGNAL(deleteSelectedRequest()),
            m_editorActions, SLOT(onDeleteAction()));

    // space bar push (request for zoom mode) is propagated from graphics view to ToolBar
    connect(m_projectionsCanvas, SIGNAL(changeActivityRequest(MaskEditorFlags::Activity)),
            m_toolBar, SLOT(onChangeActivityRequest(MaskEditorFlags::Activity)));

    m_toolBar->onChangeActivityRequest(MaskEditorFlags::HORIZONTAL_LINE_MODE);
}
