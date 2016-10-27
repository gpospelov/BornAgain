// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobQueueData.cpp
//! @brief     Implements class JobQueueData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobQueueData.h"
#include "DomainSimulationBuilder.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "JobItem.h"
#include "JobModel.h"
#include "JobWorker.h"
#include <QDebug>
#include <QThread>

JobQueueData::JobQueueData(JobModel *jobModel)
    : m_jobModel(jobModel)
{

}

//! Returns the thread for given identifier.

QThread *JobQueueData::getThread(QString identifier)
{
    QMap<QString, QThread *>::const_iterator it = m_threads.find(identifier);
    if(it != m_threads.end()) {
        return it.value();
    }
    return 0;
}

//! Returns job runner for given identifier.

JobWorker *JobQueueData::getRunner(QString identifier)
{
    QMap<QString, JobWorker *>::const_iterator it = m_runners.find(identifier);
    if(it != m_runners.end()) {
        return it.value();
    }
    return 0;
}

//! Returns the simulation (if exists) for given identifier.

GISASSimulation *JobQueueData::getSimulation(QString identifier)
{
    QMap<QString, GISASSimulation *>::const_iterator it = m_simulations.find(identifier);
    if(it != m_simulations.end()) {
        return it.value();
    }
    return 0;
}

bool JobQueueData::hasUnfinishedJobs()
{
    return m_simulations.size();
}

//! Submits job and run it in a thread.

void JobQueueData::runJob(JobItem *jobItem)
{
    QString identifier = jobItem->getIdentifier();
    if(getThread(identifier)) {
        qDebug() << "JobQueueData::runInThread() -> Thread is already running";
        return;
    }

    if(getSimulation(identifier))
        throw GUIHelpers::Error("JobQueueData::runJob() -> Error. Simulation is already existing.");

    GISASSimulation *simulation(0);
    try{
        simulation = DomainSimulationBuilder::getSimulation(jobItem->multiLayerItem(),
                                                            jobItem->instrumentItem(),
                                                            jobItem->getSimulationOptionsItem());
    } catch(const std::exception &ex) {
        QString message("JobQueueData::runJob() -> Error. "
                        "Attempt to create sample/instrument object from user description "
                        "has failed with following error message.\n\n");
        message += QString::fromStdString(std::string(ex.what()));
        jobItem->setComments(message);
        jobItem->setProgress(100);
        jobItem->setStatus(Constants::STATUS_FAILED);
        emit focusRequest(jobItem);
        return;
    }

    m_simulations[identifier] = simulation;

    JobWorker *runner = new JobWorker(identifier, simulation);
    m_runners[identifier] = runner;

    QThread *thread = new QThread();
    runner->moveToThread(thread);
    m_threads[identifier] = thread;

    // thread will start the runner
    connect(thread, SIGNAL(started()), runner, SLOT(start()));

    // after runner is finished it will tell to the thread to quit (weared behaviour)
    //connect(runner, SIGNAL(finished()), thread, SLOT(quit()));

    // finished thread will be removed from the list
    connect(thread, SIGNAL(finished()), this, SLOT(onFinishedThread()));

    // connecting the runner to started/progress slots
    connect(runner, SIGNAL(started()), this, SLOT(onStartedJob()));
    connect(runner, SIGNAL(progressUpdate()), this, SLOT(onProgressUpdate()));

    // finished job will do all cleanup
    connect(runner, SIGNAL(finished()), this, SLOT(onFinishedJob()));

    thread->start();
}

//! Cancels running job.

void JobQueueData::cancelJob(const QString &identifier)
{
    if(getThread(identifier)) {
        JobWorker *runner = getRunner(identifier);
        runner->terminate();
    }
}

//! Remove job from list completely.

void JobQueueData::removeJob(const QString &identifier)
{
    cancelJob(identifier);
    clearSimulation(identifier);
}

//! Sets JobItem properties when the job is going to start.

void JobQueueData::onStartedJob()
{
    JobWorker *runner = qobject_cast<JobWorker *>(sender());
    Q_ASSERT(runner);
    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(runner->getIdentifier());
    jobItem->setProgress(0);
    jobItem->setStatus(Constants::STATUS_RUNNING);
    jobItem->setBeginTime(GUIHelpers::currentDateTime());
    jobItem->setEndTime(QString());
}

//! Performs necessary actions when job is finished.

void JobQueueData::onFinishedJob()
{
    JobWorker *runner = qobject_cast<JobWorker *>(sender());
    Q_ASSERT(runner);

    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(runner->getIdentifier());

    processFinishedJob(runner, jobItem);

    // I tell to the thread to exit here (instead of connecting JobRunner::finished
    // to the QThread::quit because of strange behaviour)
    getThread(runner->getIdentifier())->quit();

    emit focusRequest(jobItem);

    clearSimulation(runner->getIdentifier());
    assignForDeletion(runner);

    if(!hasUnfinishedJobs())
        emit globalProgress(100);
}

void JobQueueData::onFinishedThread()
{
    QThread *thread = qobject_cast<QThread *>(sender());
    assignForDeletion(thread);
}

void JobQueueData::onProgressUpdate()
{
    JobWorker *runner = qobject_cast<JobWorker *>(sender());
    Q_ASSERT(runner);
    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(runner->getIdentifier());
    jobItem->setProgress(runner->getProgress());
    updateGlobalProgress();
}

//! Estimates global progress from the progress of multiple running jobs and
//! emmits appropriate signal.

void JobQueueData::updateGlobalProgress()
{
    int global_progress(0);
    int nRunningJobs(0);
    QModelIndex parentIndex;
    for(int i_row = 0; i_row < m_jobModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_jobModel->index( i_row, 0, parentIndex );
        JobItem *jobItem = m_jobModel->getJobItemForIndex(itemIndex);
        if(jobItem->isRunning()) {
            global_progress += jobItem->getProgress();
            nRunningJobs++;
        }
    }
    if(nRunningJobs) {
        global_progress /= nRunningJobs;
    } else {
        global_progress=-1;
    }
    emit globalProgress(global_progress);
}

//! Cancels all running jobs.

void JobQueueData::onCancelAllJobs()
{
    QStringList keys = m_threads.keys();
    foreach(QString key, keys) {
        cancelJob(key);
    }
}

//! Removes QThread from the map of known threads, assigns it for deletion.

void JobQueueData::assignForDeletion(QThread *thread)
{
    Q_ASSERT(thread);
    for(auto it=m_threads.begin(); it!=m_threads.end(); ++it) {
        if(it.value() == thread) {
            thread->deleteLater();
            m_threads.erase(it);
            return;
        }
    }
    throw GUIHelpers::Error("JobQueueData::assignForDeletion() -> Error! Can't find thread.");
}

//! Removes JobRunner from the map of known runners, assigns it for deletion.

void JobQueueData::assignForDeletion(JobWorker *runner)
{
    Q_ASSERT(runner);
    runner->disconnect();
    for(auto it=m_runners.begin(); it!=m_runners.end(); ++it) {
        if(it.value() == runner) {
            runner->deleteLater();
            m_runners.erase(it);
            return;
        }
    }
    throw GUIHelpers::Error("JobQueueData::assignForDeletion() -> Error! Can't find the runner.");
}

void JobQueueData::clearSimulation(const QString &identifier)
{
    GISASSimulation *simulation = getSimulation(identifier);
    m_simulations.remove(identifier);
    delete simulation;
}

//! Set all data of finished job

void JobQueueData::processFinishedJob(JobWorker *runner, JobItem *jobItem)
{
    jobItem->setEndTime(GUIHelpers::currentDateTime());
    jobItem->setDuration(runner->getSimulationDuration());

    // propagating status of runner
    jobItem->setStatus(runner->getStatus());
    if(jobItem->isFailed()) {
        jobItem->setComments(runner->getFailureMessage());
    } else {
        // propagating simulation results
        GISASSimulation *simulation = getSimulation(runner->getIdentifier());
        jobItem->setResults(simulation);
    }

    // fixing job progress (if job was successfull, but due to wrong estimation, progress not 100%)
    if(jobItem->isCompleted())
        jobItem->setProgress(100);
}
