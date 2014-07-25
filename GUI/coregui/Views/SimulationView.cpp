#include "SimulationView.h"
#include "qdebug.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "SimulationDataModel.h"
#include "mainwindow.h"
#include "JobQueueModel.h"
#include "QVBoxLayout"

SimulationView::SimulationView(SimulationDataModel *p_simulation_data_model, JobQueueModel *jobQueueModel, SampleModel *sampleModel, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
    , m_jobQueueModel(jobQueueModel)
    , m_sampleModel(sampleModel)
{
    m_simulationSetupWidget = new SimulationSetupWidget(mp_simulation_data_model);
    m_simulationSetupWidget->setJobQueueModel(m_jobQueueModel);

    m_quickSimulationWidget = new QuickSimulationWidget(m_sampleModel);

    m_tabWidget = new QTabWidget();
    m_tabWidget->insertTab(SimulationSetupTab, m_simulationSetupWidget, tr("Simulation Params"));
    m_tabWidget->insertTab(QuickSimulationTab, m_quickSimulationWidget, tr("Quick Simulation"));

    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);
}

void SimulationView::updateSimulationViewElements()
{
    m_simulationSetupWidget->updateViewElements();
    m_quickSimulationWidget->updateViews();
}

void SimulationView::onChangeTabWidget(int index)
{
    if(index == SimulationSetupTab)
    {
        m_simulationSetupWidget->updateViewElements();
    }
    else if(index == QuickSimulationTab)
    {
        m_quickSimulationWidget->updateViews();
    }
}
