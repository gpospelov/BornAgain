#include "QuickSimulationRunner.h"
#include "Simulation.h"
#include "JobQueueData.h"
#include "JobQueueItem.h"
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

    JobItem *item = m_jobQueueData->getJobItem(identifier);
    connect(item, SIGNAL(modified(JobItem*)), this, SLOT(onJobItemIsModified(JobItem*)));

    m_jobQueueData->runJob(identifier);


    //m_simulation_in_progress = false;
}

bool QuickSimulationRunner::isSimulationInProgress() const
{
    return m_simulation_in_progress;
}

void QuickSimulationRunner::onJobItemIsModified(JobItem *item)
{
    qDebug() << "QuickSimulationRunner::onJobItemIsModified()";
}

