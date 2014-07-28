#include "QuickSimulationRunner.h"
#include "Simulation.h"
#include "JobQueueData.h"
#include "JobQueueItem.h"
#include "JobItem.h"
#include "PlotWidget.h"
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

    JobItem *item = m_jobQueueData->getJobItem(identifier);
    connect(item, SIGNAL(modified(JobItem*)), this, SLOT(onJobItemIsModified(JobItem*)));

    connect(m_jobQueueData, SIGNAL(jobIsFinished(QString)), this, SLOT(onFinishedJob(QString)));

    m_jobQueueData->runJob(identifier);


    //m_simulation_in_progress = false;
}

bool QuickSimulationRunner::isSimulationInProgress() const
{
    return m_simulation_in_progress;
}

void QuickSimulationRunner::setPlotWidget(PlotWidget *plotWidget)
{
    m_plotWidget = plotWidget;
}


void QuickSimulationRunner::onJobItemIsModified(JobItem *item)
{
//    qDebug() << "QuickSimulationRunner::onJobItemIsModified()" << item->getProgress();

}


void QuickSimulationRunner::onFinishedJob(const QString &identifier)
{
    qDebug() << "QuickSimulationRunner::onFinishedJob()" << identifier;



    qDebug() << " m_job_items" << m_jobQueueData->m_job_items.size()
             << " m_threads" << m_jobQueueData->m_threads.size()
             << " m_runners" << m_jobQueueData->m_runners.size()
             << " m_simulations" << m_jobQueueData->m_simulations.size();

    JobItem *item = m_jobQueueData->getJobItem(identifier);
    qDebug() << "XXX " << item << item->getOutputDataItem();
    m_plotWidget->drawPlot(item->getOutputDataItem());

    m_simulation_in_progress = false;
}

