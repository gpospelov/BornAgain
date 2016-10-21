// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditor.cpp
//! @brief     Implements class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskEditor.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"
#include "MaskEditorActions.h"
#include "MaskEditorCanvas.h"
#include "MaskEditorPropertyPanel.h"
#include "MaskEditorToolBar.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskItems.h"
#include "MultiLayer.h"
#include "SampleBuilderFactory.h"
#include "SessionModel.h"
#include "SimulationFactory.h"
#include "minisplitter.h"
#include <QBoxLayout>
#include <QContextMenuEvent>
#include <QDebug>
#include <QMenu>

MaskEditor::MaskEditor(QWidget* parent)
    : QMainWindow(parent)
    , m_editorActions(new MaskEditorActions(this))
    , m_toolBar(new MaskEditorToolBar(m_editorActions))
    , m_editorPropertyPanel(new MaskEditorPropertyPanel)
    , m_editorCanvas(new MaskEditorCanvas)
    , m_splitter(new Manhattan::MiniSplitter)
{
    setObjectName(QStringLiteral("MaskEditor"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_splitter->addWidget(m_editorCanvas);
    m_splitter->addWidget(m_editorPropertyPanel);
    m_splitter->setCollapsible(1, true);

    addToolBar(Qt::RightToolBarArea, m_toolBar);

    setCentralWidget(m_splitter);

    setup_connections();

    m_editorPropertyPanel->setPanelHidden(true);
}

void MaskEditor::setMaskContext(SessionModel* model, const QModelIndex &maskContainerIndex,
                                IntensityDataItem* intensityItem)
{
    m_editorPropertyPanel->setMaskContext(model, maskContainerIndex, intensityItem);

    Q_ASSERT(intensityItem);
    Q_ASSERT(maskContainerIndex.isValid());
    Q_ASSERT(model->itemForIndex(maskContainerIndex)->modelType() == Constants::MaskContainerType);

    m_editorCanvas->setMaskContext(model, maskContainerIndex, intensityItem);
    m_editorCanvas->setSelectionModel(m_editorPropertyPanel->selectionModel());

    m_editorActions->setModel(model, maskContainerIndex);
    m_editorActions->setSelectionModel(m_editorPropertyPanel->selectionModel());
}

//! shows/hides right panel with properties
void MaskEditor::onPropertyPanelRequest()
{
    m_editorPropertyPanel->setPanelHidden(!m_editorPropertyPanel->isHidden());
}

//! Context menu reimplemented to supress default menu
void MaskEditor::contextMenuEvent(QContextMenuEvent* event)
{
    Q_UNUSED(event);
}

//! Returns list of actions intended for styled toolbar (on the top).

QList<QAction *> MaskEditor::topToolBarActions()
{
    return m_editorActions->topToolBarActions();
}

void MaskEditor::setup_connections()
{
    // reset view request is propagated from editorActions to graphics view
    connect(m_editorActions,
            SIGNAL(resetViewRequest()),
            m_editorCanvas,
            SLOT(onResetViewRequest())
            );

    // tool panel request is propagated from editorActions to this MaskEditor
    connect(m_editorActions,
            SIGNAL(propertyPanelRequest()),
            this,
            SLOT(onPropertyPanelRequest())
            );

    // save plot request is propagated from editorActions to graphics scene
    connect(m_editorActions,
            SIGNAL(savePlotRequest()),
            m_editorCanvas,
            SLOT(onSavePlotRequest())
            );

    // selection/drawing activity is propagated from ToolBar to graphics scene
    connect(m_toolBar,
            SIGNAL(activityModeChanged(MaskEditorFlags::Activity)),
            m_editorCanvas->getScene(),
            SLOT(onActivityModeChanged(MaskEditorFlags::Activity))
            );

    // mask value is propagated from ToolBar to graphics scene
    connect(m_toolBar,
            SIGNAL(maskValueChanged(MaskEditorFlags::MaskValue)),
            m_editorCanvas->getScene(),
            SLOT(onMaskValueChanged(MaskEditorFlags::MaskValue))
            );

    // show results request is propagated from ToolBar to Canvas
    connect(m_toolBar,
            SIGNAL(presentationTypeRequest(MaskEditorFlags::PresentationType)),
            m_editorCanvas,
            SLOT(onPresentationTypeRequest(MaskEditorFlags::PresentationType))
            );

    // space bar push (request for zoom mode) is propagated from graphics view to ToolBar
    connect(m_editorCanvas,
            SIGNAL(changeActivityRequest(MaskEditorFlags::Activity)),
            m_toolBar,
            SLOT(onChangeActivityRequest(MaskEditorFlags::Activity))
            );

    // context menu request is propagated from graphics scene to MaskEditorActions
    connect(m_editorCanvas->getScene(),
            SIGNAL(itemContextMenuRequest(QPoint)),
            m_editorActions,
            SLOT(onItemContextMenuRequest(QPoint))
            );

    // context menu request is propagated from PropertyPanel to MaskEditorActions
    connect(m_editorPropertyPanel,
            SIGNAL(itemContextMenuRequest(QPoint)),
            m_editorActions,
            SLOT(onItemContextMenuRequest(QPoint))
            );
}
