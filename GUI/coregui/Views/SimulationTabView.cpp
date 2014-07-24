#include "SimulationTabView.h"
#include "qdebug.h"

#include "SimulationDataModel.h"
#include "mainwindow.h"
#include "JobQueueModel.h"
#include "QVBoxLayout"

SimulationTabView::SimulationTabView(SimulationDataModel *p_simulation_data_model, JobQueueModel *jobQueueModel, SessionModel *sessionModel, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
    , m_jobQueueModel(jobQueueModel)
    , m_sessionModel(sessionModel)
{
    m_simulationView = new SimulationView(mp_simulation_data_model);
    m_simulationView->setJobQueueModel(m_jobQueueModel);

    m_quickSimulationView = new QuickSimulationView(m_sessionModel);

    m_tabWidget = new QTabWidget();
    m_tabWidget->insertTab(SimulationParamsTab, m_simulationView, tr("Simulation Params"));
    m_tabWidget->insertTab(QuickSimulationTab, m_quickSimulationView, tr("Quick Simulation"));

    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);
}

void SimulationTabView::updateSimulationViewElements()
{
    m_simulationView->updateViewElements();
    m_quickSimulationView->updateViews();
}

void SimulationTabView::onChangeTabWidget(int index)
{
    if(index == SimulationParamsTab)
    {
        m_simulationView->updateViewElements();
    }
    else if(index == QuickSimulationTab)
    {
        m_quickSimulationView->updateViews();
    }
}
