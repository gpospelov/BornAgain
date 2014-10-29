#include "SimulationView.h"
#include "SimulationSetupWidget.h"
#include "styledtoolbar.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "JobQueueModel.h"
#include "mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDebug>

SimulationView::SimulationView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_jobQueueModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    m_jobQueueModel = mainWindow->getJobQueueModel();
    m_sampleModel = mainWindow->getSampleModel();
    m_instrumentModel = mainWindow->getInstrumentModel();

    m_simulationSetupWidget = new SimulationSetupWidget();
    m_simulationSetupWidget->setJobQueueModel(m_jobQueueModel);
    m_simulationSetupWidget->setSampleModel(m_sampleModel);
    m_simulationSetupWidget->setInstrumentModel(m_instrumentModel);

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
    qDebug() << "SimulationView::updateSimulationViewElements()" << m_sampleModel << m_instrumentModel;
    m_simulationSetupWidget->updateViewElements();
}


void SimulationView::onRunSimulationShortcut()
{
    qDebug() << "SimulationView::onRunSimulationShortcut()";
    m_simulationSetupWidget->onRunSimulation();
}
