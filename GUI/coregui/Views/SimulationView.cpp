#include "SimulationView.h"
#include "SimulationSetupWidget.h"
#include "QuickSimulationWidget.h"
#include "SimulationToolBar.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "SimulationDataModel.h"
#include "JobQueueModel.h"
#include "qdebug.h"
#include "mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>


SimulationView::SimulationView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , mp_simulation_data_model(0)
    , m_jobQueueModel(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    mp_simulation_data_model = mainWindow->getSimulationDataModel();
    m_jobQueueModel = mainWindow->getJobQueueModel();
    m_sampleModel = mainWindow->getSampleModel();
    m_instrumentModel = mainWindow->getInstrumentModel();

    m_simulationSetupWidget = new SimulationSetupWidget(mp_simulation_data_model);
    m_simulationSetupWidget->setJobQueueModel(m_jobQueueModel);

    m_quickSimulationWidget = new QuickSimulationWidget(m_sampleModel, m_instrumentModel);

    m_tabWidget = new QTabWidget();
    m_tabWidget->insertTab(SimulationSetupTab, m_simulationSetupWidget, tr("Simulation Params"));
    m_tabWidget->insertTab(QuickSimulationTab, m_quickSimulationWidget, tr("Quick Simulation"));

    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));

    m_toolBar = new SimulationToolBar(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_tabWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void SimulationView::updateSimulationViewElements()
{
    m_simulationSetupWidget->updateViewElements();
//    m_quickSimulationWidget->updateViews(m_simulationSetupWidget->getInstrumentSelection(), m_simulationSetupWidget->getSampleSelection());
    delete reinterpret_cast<QString*>(0xFEE1DEAD);
}

void SimulationView::onChangeTabWidget(int index)
{
    if(index == SimulationSetupTab)
    {
        //m_simulationSetupWidget->updateViewElements();
    }
    else if(index == QuickSimulationTab)
    {
        m_quickSimulationWidget->updateViews(m_simulationSetupWidget->getInstrumentSelection(), m_simulationSetupWidget->getSampleSelection());
    }
}
