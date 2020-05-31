// ************************************************************************** //
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
// ************************************************************************** //

#include "SampleView.h"
#include "ApplicationModels.h"
#include "SampleDesigner.h"
#include "SampleToolBar.h"
#include "SampleTreeWidget.h"
#include "SampleViewActions.h"
#include "SampleViewDocks.h"
#include "SampleViewStatusBar.h"
#include "mainwindow.h"
#include <QMenu>
#include <memory>

SampleView::SampleView(MainWindow* mainWindow)
    : Manhattan::FancyMainWindow(mainWindow), m_models(mainWindow->models()),
      m_docks(new SampleViewDocks(this)),
      m_actions(new SampleViewActions(mainWindow->models()->sampleModel(), this)),
      m_toolBar(nullptr), m_statusBar(new SampleViewStatusBar(mainWindow))
{
    setObjectName("SampleView");
    m_actions->setSelectionModel(selectionModel());

    connectSignals();
}

ApplicationModels* SampleView::models()
{
    return m_models;
}

SampleViewDocks* SampleView::docks()
{
    return m_docks;
}

void SampleView::onDockMenuRequest()
{
    std::unique_ptr<QMenu> menu(createPopupMenu());
    menu->exec(QCursor::pos());
}

void SampleView::showEvent(QShowEvent* event)
{
    if (isVisible())
        m_statusBar->show();
    Manhattan::FancyMainWindow::showEvent(event);
}

void SampleView::hideEvent(QHideEvent* event)
{
    if (isHidden())
        m_statusBar->hide();
    Manhattan::FancyMainWindow::hideEvent(event);
}

void SampleView::connectSignals()
{
    connect(this, &SampleView::resetLayout, m_docks, &SampleViewDocks::onResetLayout);
    connect(m_statusBar, &SampleViewStatusBar::dockMenuRequest, this,
            &SampleView::onDockMenuRequest);

    // toolBar should be initialized after MaterialBrowser
    m_toolBar = new SampleToolBar(m_actions, this);
    connect(m_toolBar, SIGNAL(deleteItems()), sampleDesigner()->getView(),
            SLOT(deleteSelectedItems()));
    connect(m_toolBar, SIGNAL(selectionMode(int)), sampleDesigner()->getView(),
            SLOT(onSelectionMode(int)));
    connect(sampleDesigner()->getView(), SIGNAL(selectionModeChanged(int)), m_toolBar,
            SLOT(onViewSelectionMode(int)));
    connect(m_toolBar, SIGNAL(centerView()), sampleDesigner()->getView(), SLOT(onCenterView()));
    connect(m_toolBar, SIGNAL(changeScale(double)), sampleDesigner()->getView(),
            SLOT(onChangeScale(double)));

    connect(sampleDesigner()->getScene(), SIGNAL(selectionModeChangeRequest(int)),
            sampleDesigner()->getView(), SLOT(onSelectionMode(int)));

    addToolBar(m_toolBar);
}

QItemSelectionModel* SampleView::selectionModel()
{
    return m_docks->treeWidget()->treeView()->selectionModel();
}

SampleDesigner* SampleView::sampleDesigner()
{
    return m_docks->sampleDesigner();
}
