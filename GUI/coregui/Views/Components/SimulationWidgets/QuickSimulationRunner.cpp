#include "QuickSimulationRunner.h"
#include "Simulation.h"
#include "JobQueueData.h"
#include "JobQueueItem.h"
#include "JobItem.h"
#include "OutputDataWidget.h"
#include "GUIHelpers.h"
#include <QDebug>

QuickSimulationRunner::QuickSimulationRunner(QObject *parent)
    : QObject(parent)
    , m_jobQueueData(new JobQueueData)
    , m_simulation_in_progress(false)
{

}

QuickSimulationRunner::~QuickSimulationRunner()
{
    delete m_jobQueueData;
}

void QuickSimulationRunner::runSimulation(Simulation *simulation)
{
    Q_ASSERT(simulation);
    qDebug() << "RealTimeSimulation::runSimulation() ->";

    if(m_simulation_in_progress) {
        qDebug() << "RealTimeSimulation::runSimulation() -> Simulation in progress";
        return;
    }

    m_simulation_in_progress = true;


    QString identifier = m_jobQueueData->createJob("QuickSimulation", simulation);
    qDebug() << "QuickSimulationRunner::runSimulation() ->> created job" << identifier << m_jobQueueData->getJobItem(identifier);

//    JobItem *item = m_jobQueueData->getJobItem(identifier);
//    connect(item, SIGNAL(modified(JobItem*)), this, SLOT(onJobItemIsModified(JobItem*)));

    connect(m_jobQueueData, SIGNAL(jobIsFinished(QString)), this, SLOT(onFinishedJob(QString)));

    m_jobQueueData->runJob(identifier);


    //m_simulation_in_progress = false;
}

bool QuickSimulationRunner::isSimulationInProgress() const
{
    return m_simulation_in_progress;
}

void QuickSimulationRunner::setOutputDataWidget(OutputDataWidget *outputDataWidget)
{
    m_outputDataWidget = outputDataWidget;
}


void QuickSimulationRunner::onJobItemIsModified(JobItem *item)
{
//    qDebug() << "QuickSimulationRunner::onJobItemIsModified()" << item->getProgress();

}


void QuickSimulationRunner::onFinishedJob(const QString &identifier)
{
    qDebug() << "QuickSimulationRunner::onFinishedJob()" << identifier << m_current_identifier;

    if(identifier != m_current_identifier) {
        if(m_outputDataWidget)
            m_outputDataWidget->setCurrentItem(0);

        qDebug() << "QuickSimulationRunner::onFinishedJob() -> removing job" << identifier;
        m_jobQueueData->removeJob(m_current_identifier);

        m_current_identifier = identifier;
    }


    qDebug() << " m_job_items" << m_jobQueueData->m_job_items.size()
             << " m_threads" << m_jobQueueData->m_threads.size()
             << " m_runners" << m_jobQueueData->m_runners.size()
             << " m_simulations" << m_jobQueueData->m_simulations.size();

    JobItem *item = m_jobQueueData->getJobItem(identifier);
    qDebug() << "XXX " << item << item->getOutputDataItem();
    if(!m_outputDataWidget)
    {
        m_outputDataWidget = new OutputDataWidget(0, false);
        m_outputDataWidget->setPropertyPanelVisible(false);
    }
    m_outputDataWidget->setCurrentItem(item->getOutputDataItem());

    m_simulation_in_progress = false;
}

