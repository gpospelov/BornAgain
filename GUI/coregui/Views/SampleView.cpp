//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleView.cpp
//! @brief     Implements class SampleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/SampleView.h"
#include "Base/Utils/Assert.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/FilterPropertyProxy.h"
#include "GUI/coregui/Views/CommonWidgets/DocksController.h"
#include "GUI/coregui/Views/SampleDesigner/RealSpacePanel.h"
#include "GUI/coregui/Views/SampleDesigner/SampleDesigner.h"
#include "GUI/coregui/Views/SampleDesigner/SamplePropertyWidget.h"
#include "GUI/coregui/Views/SampleDesigner/SampleToolBar.h"
#include "GUI/coregui/Views/SampleDesigner/SampleTreeWidget.h"
#include "GUI/coregui/Views/SampleDesigner/SampleWidgetBox.h"
#include "GUI/coregui/Views/SampleDesigner/ScriptPanel.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QDockWidget>
#include <QMenu>
#include <memory>

SampleView::SampleView(MainWindow* mainWindow)
    : QMainWindow(mainWindow), m_docks(new DocksController(this)) {

    setObjectName("SampleView");
    createSubWindows();
    connectSignals();
}

ApplicationModels* SampleView::models() {
    return MainWindow::instance()->models();
}

void SampleView::toggleRealSpaceView() {
    m_docks->toggleDock(REALSPACEPANEL);
}

void SampleView::addDockActionsToMenu(QMenu* menu) {
    m_docks->addDockActionsToMenu(menu);

    menu->addSeparator();

    QAction* action = new QAction(menu);
    action->setText("Reset to default layout");
    connect(action, &QAction::triggered, this, &SampleView::resetLayout);
    menu->addAction(action);
}

void SampleView::createSubWindows() {
    m_sampleDesigner = new SampleDesigner(this);
    m_widgetBox = new SampleWidgetBox(m_sampleDesigner, this);
    m_treeWidget = new SampleTreeWidget(this, models()->sampleModel());
    m_propertyWidget = new SamplePropertyWidget(m_treeWidget->treeView()->selectionModel(), this);
    m_scriptPanel = new ScriptPanel(this);
    m_realSpacePanel = new RealSpacePanel(models()->sampleModel(),
                                          m_treeWidget->treeView()->selectionModel(), this);

    m_docks->addWidget(WIDGET_BOX, m_widgetBox, Qt::LeftDockWidgetArea);
    m_docks->addWidget(SAMPLE_TREE, m_treeWidget, Qt::RightDockWidgetArea);
    m_docks->addWidget(PROPERTY_EDITOR, m_propertyWidget, Qt::RightDockWidgetArea);
    m_docks->addWidget(INFO, m_scriptPanel, Qt::BottomDockWidgetArea);
    m_docks->addWidget(REALSPACEPANEL, m_realSpacePanel, Qt::BottomDockWidgetArea);

    connect(m_scriptPanel, &ScriptPanel::widgetHeightRequest, m_docks,
            &DocksController::setDockHeightForWidget);

    m_scriptPanel->setSampleModel(models()->sampleModel());
    m_scriptPanel->setInstrumentModel(models()->instrumentModel());

    m_sampleDesigner->setModels(models());
    m_sampleDesigner->setSelectionModel(
        m_treeWidget->treeView()->selectionModel(),
        dynamic_cast<FilterPropertyProxy*>(
            const_cast<QAbstractItemModel*>(m_treeWidget->treeView()->model())));

    setCentralWidget(m_sampleDesigner->getCentralWidget());
    resetLayout();
}

void SampleView::connectSignals() {
    // toolBar should be initialized after MaterialBrowser
    m_toolBar = new SampleToolBar(this);
    connect(m_toolBar, &SampleToolBar::deleteItems, m_sampleDesigner->getView(),
            &DesignerView::deleteSelectedItems);
    connect(m_toolBar, &SampleToolBar::selectionMode, m_sampleDesigner->getView(),
            &DesignerView::onSelectionMode);
    connect(m_sampleDesigner->getView(), &DesignerView::selectionModeChanged, m_toolBar,
            &SampleToolBar::onViewSelectionMode);
    connect(m_toolBar, &SampleToolBar::centerView, m_sampleDesigner->getView(),
            &DesignerView::onCenterView);
    connect(m_toolBar, &SampleToolBar::changeScale, m_sampleDesigner->getView(),
            &DesignerView::onChangeScale);
    connect(m_sampleDesigner->getScene(), &DesignerScene::selectionModeChangeRequest,
            m_sampleDesigner->getView(), &DesignerView::onSelectionMode);

    addToolBar(m_toolBar);
}

void SampleView::resetLayout() {
    m_docks->resetLayout();
    tabifyDockWidget(m_docks->findDock(REALSPACEPANEL), m_docks->findDock(INFO));
    m_docks->findDock(REALSPACEPANEL)->raise(); // makes first tab active

    m_docks->findDock(REALSPACEPANEL)->hide();
    m_docks->findDock(INFO)->hide();
}
