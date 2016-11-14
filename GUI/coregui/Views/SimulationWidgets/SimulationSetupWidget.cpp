// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationSetupWidget.cpp
//! @brief     Implements class SimulationSetupWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationSetupWidget.h"
#include "AppSvc.h"
#include "ApplicationModels.h"
#include "DocumentModel.h"
#include "JobItem.h"
#include "JobModel.h"
#include "PythonScriptWidget.h"
#include "SimulationDataSelectorWidget.h"
#include "SimulationOptionsWidget.h"
#include "SimulationSetupAssistant.h"
#include "projectmanager.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

SimulationSetupWidget::SimulationSetupWidget(QWidget *parent)
    : QWidget(parent)
    , m_applicationModels(0)
    , runSimulationButton(0)
    , exportToPyScriptButton(0)
    , m_simDataSelectorWidget(new SimulationDataSelectorWidget(this))
    , m_simOptionsWidget(new SimulationOptionsWidget(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_simDataSelectorWidget);
    mainLayout->addWidget(m_simOptionsWidget);
    mainLayout->addWidget(createButtonWidget());
    mainLayout->addStretch(10);
    setLayout(mainLayout);

    // signal and slots
    connect(runSimulationButton, SIGNAL(clicked()), this, SLOT(onRunSimulation()));
    connect(exportToPyScriptButton, SIGNAL(clicked()), this, SLOT(onExportToPythonScript()));
}

void SimulationSetupWidget::setApplicationModels(ApplicationModels *model)
{
    Q_ASSERT(model);
    if(model != m_applicationModels) {
        m_applicationModels = model;
        m_simDataSelectorWidget->setApplicationModels(model);
        updateViewElements();
    }
}

void SimulationSetupWidget::updateViewElements()
{
    m_simDataSelectorWidget->updateViewElements();
    m_simOptionsWidget->setItem(m_applicationModels->documentModel()->getSimulationOptionsItem());
}

void SimulationSetupWidget::onRunSimulation()
{
    const MultiLayerItem *multiLayerItem = m_simDataSelectorWidget->selectedMultiLayerItem();
    const InstrumentItem *instrumentItem = m_simDataSelectorWidget->selectedInstrumentItem();
    const RealDataItem *realDataItem = m_simDataSelectorWidget->selectedRealDataItem();

    SimulationSetupAssistant assistant;
    if(!assistant.isValidSimulationSetup(multiLayerItem, instrumentItem, realDataItem))
        return;

    JobItem *jobItem = m_applicationModels->jobModel()->addJob(
                multiLayerItem,
                instrumentItem,
                realDataItem,
                m_applicationModels->documentModel()->getSimulationOptionsItem());

    if (jobItem->runImmediately() || jobItem->runInBackground())
        m_applicationModels->jobModel()->runJob(jobItem->index());
}

void SimulationSetupWidget::onExportToPythonScript()
{
    const MultiLayerItem *multiLayerItem = m_simDataSelectorWidget->selectedMultiLayerItem();
    const InstrumentItem *instrumentItem = m_simDataSelectorWidget->selectedInstrumentItem();

    SimulationSetupAssistant assistant;
    if(!assistant.isValidSimulationSetup(multiLayerItem, instrumentItem))
        return;

    PythonScriptWidget *pythonWidget = new PythonScriptWidget(this);
    pythonWidget->show();
    pythonWidget->raise();
    pythonWidget->generatePythonScript(
        multiLayerItem, instrumentItem,
        m_applicationModels->documentModel()->getSimulationOptionsItem(),
        AppSvc::projectManager()->getProjectDir());
}

QWidget *SimulationSetupWidget::createButtonWidget()
{
    QWidget *result = new QWidget;

    QHBoxLayout *simButtonLayout = new QHBoxLayout;
    // run simulation button
    runSimulationButton = new QPushButton("Run Simulation");
    runSimulationButton->setIcon(QIcon(":/images/main_simulation.png"));
    runSimulationButton->setMinimumWidth(100);
    runSimulationButton->setMinimumHeight(50);
    runSimulationButton->setToolTip("Run the simulation using settings above.\n"
                                    " Global shortcut ctrl-r can be used to run from sample view.");
//    QPalette palette = runSimulationButton->palette();
//    palette.setColor(QPalette::Button, QColor(Constants::BUTTON_COLOR));
//    palette.setColor(QPalette::ButtonText, QColor(Constants::BUTTON_TEXT_COLOR));
//    runSimulationButton->setPalette(palette);

    // export simulation to a python script
    exportToPyScriptButton = new QPushButton("Export to Python Script");
    exportToPyScriptButton->setIcon(QIcon(":/images/mode_script.png"));
    exportToPyScriptButton->setMinimumWidth(100);
    exportToPyScriptButton->setMinimumHeight(50);
    exportToPyScriptButton->setToolTip("Export the simulation using settings above to "
                                       "a python script.\n");
//    exportToPyScriptButton->setPalette(palette);

    simButtonLayout->addStretch();
    simButtonLayout->addWidget(runSimulationButton);
    simButtonLayout->addWidget(exportToPyScriptButton);
    simButtonLayout->addStretch();

    result->setLayout(simButtonLayout);

    return result;
}
