// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SimulationView.cpp
//! @brief     Implements class SimulationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationView.h"
#include "SimulationSetupWidget.h"
#include "styledtoolbar.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDebug>

SimulationView::SimulationView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_jobModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    m_jobModel = mainWindow->jobModel();
    m_sampleModel = mainWindow->sampleModel();
    m_instrumentModel = mainWindow->instrumentModel();

    m_simulationSetupWidget = new SimulationSetupWidget();
    m_simulationSetupWidget->setJobModel(m_jobModel);
    m_simulationSetupWidget->setSampleModel(m_sampleModel);
    m_simulationSetupWidget->setInstrumentModel(m_instrumentModel);
    m_simulationSetupWidget->setProjectManager(mainWindow->getProjectManager());

    m_toolBar = new StyledToolBar(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_simulationSetupWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}


void SimulationView::updateSimulationViewElements()
{
    //qDebug() << "SimulationView::updateSimulationViewElements()" << m_sampleModel << m_instrumentModel;
    m_simulationSetupWidget->updateViewElements();
}

void SimulationView::onRunSimulationShortcut()
{
    //qDebug() << "SimulationView::onRunSimulationShortcut()";
    m_simulationSetupWidget->onRunSimulation();
}
