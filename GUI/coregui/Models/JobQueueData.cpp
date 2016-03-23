// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobQueueData.cpp
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
#include "GISASSimulation.h"
#include "AngleProperty.h"
#include "InstrumentItem.h"
#include "InstrumentModel.h"
#include "DetectorItems.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "JobModel.h"
#include "JobRunner.h"
#include "DomainSimulationBuilder.h"
#include "ThreadInfo.h"
#include "GUIHelpers.h"
#include <QUuid>
#include <QThread>
#include <QDateTime>
#include <QDebug>


//! Creates JobQueueItem and corresponding JobItem.
//! Created JobItem will be registered using unique identifier.
JobQueueData::JobQueueData(JobModel *jobModel)
    : m_jobModel(jobModel)
{

}

//! returns the thread (if exists) for given identifier
QThread *JobQueueData::getThread(QString identifier)
{
    QMap<QString, QThread *>::const_iterator it = m_threads.find(identifier);
    if(it != m_threads.end()) {
        return it.value();
    }
    return 0;
}


//! returns job runner (if exists) for given identifier
JobRunner *JobQueueData::getRunner(QString identifier)
{
    QMap<QString, JobRunner *>::const_iterator it = m_runners.find(identifier);
    if(it != m_runners.end()) {
        return it.value();
    }
    return 0;
}


//! returns the simulation (if exists) for given identifier
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

//void JobQueueData::setResults(JobItem *jobItem, const GISASSimulation *simulation)
//{
//    if(!simulation)
//        throw GUIHelpers::Error("NJobItem::setResults() -> Error. Null simulation.");

//    jobItem->setResults(simulation);
////    IntensityDataItem *intensityItem = jobItem->getIntensityDataItem();

////    if(!intensityItem) {
////        intensityItem = static_cast<IntensityDataItem *>(m_jobModel->insertNewItem(Constants::IntensityDataType, m_jobModel->indexOfItem(jobItem)));
////    }
////    intensityItem->setNameFromProposed(jobItem->itemName());
//////    intensityItem->setOutputData(simulation->getDetectorIntensity());
////    intensityItem->setResults(simulation);
//}

void JobQueueData::runJob(const QString &identifier)
{
    qDebug() << "JobQueueData::runJob(const QString &identifier)";
    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(identifier);
    runJob(jobItem);
}

//! submit job and run it in a thread
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
        simulation = DomainSimulationBuilder::getSimulation(jobItem->getMultiLayerItem(),
                                                            jobItem->getInstrumentItem());
    } catch(const std::exception &ex) {
        QString message("JobQueueData::runJob() -> Error. Attempt to create sample/instrument object from user description "
                        "has failed with following error message.\n\n");
        message += QString::fromStdString(std::string(ex.what()));
        jobItem->setComments(message);
        jobItem->setProgress(100);
        jobItem->setStatus(Constants::STATUS_FAILED);
        emit focusRequest(identifier);
        emit jobIsFinished(identifier);
        return;
    }

    ThreadInfo info;
    info.n_threads = jobItem->getNumberOfThreads();
    simulation->setThreadInfo(info);
    m_simulations[identifier] = simulation;

    JobRunner *runner = new JobRunner(identifier, simulation);
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

    qDebug() << "JobQueueData::runInThread() starting thread";
    thread->start();
}


//! cancels running job
void JobQueueData::cancelJob(const QString &identifier)
{
    qDebug() << "JobQueueData::cancelJob()";
    if(getThread(identifier)) {
        JobRunner *runner = getRunner(identifier);
        runner->terminate();
        return;
    }
    //qDebug() << "JobQueueData::cancelJob() -> No thread is running";
}


//! remove job from list completely
void JobQueueData::removeJob(const QString &identifier)
{
    qDebug() << "JobQueueData::removeJob" << identifier;
    cancelJob(identifier);
    clearSimulation(identifier);
}

void JobQueueData::onStartedJob()
{
    qDebug() << "JobQueueData::onStartedJob()";
    JobRunner *runner = qobject_cast<JobRunner *>(sender());
    Q_ASSERT(runner);
    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(runner->getIdentifier());
    jobItem->setProgress(0);
    jobItem->setStatus(Constants::STATUS_RUNNING);
    QString begin_time = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    jobItem->setBeginTime(begin_time);
    jobItem->setEndTime("");
}

void JobQueueData::onFinishedJob()
{
    qDebug() << "JobQueueData::onFinishedJob()";

    JobRunner *runner = qobject_cast<JobRunner *>(sender());
    Q_ASSERT(runner);

    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(runner->getIdentifier());

    QString end_time = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    jobItem->setEndTime(end_time);


    // propagating status of runner
    jobItem->setStatus(runner->getStatus());
    if(jobItem->isFailed()) {
        jobItem->setComments(runner->getFailureMessage());
    } else {
        // propagating simulation results
        GISASSimulation *simulation = getSimulation(runner->getIdentifier());
        jobItem->setResults(simulation);
    }

    // I tell to the thread to exit here (instead of connecting JobRunner::finished to the QThread::quit because of strange behaviour)
    getThread(runner->getIdentifier())->quit();

    if(jobItem->runImmediately())
        emit focusRequest(runner->getIdentifier());

    emit jobIsFinished(runner->getIdentifier());

    clearSimulation(runner->getIdentifier());
    assignForDeletion(runner);
//    qDebug() << "     JobQueueData::onFinishedJob() -> after emiting jobIsFinished(), after asigning runner for deletion";

    if(!hasUnfinishedJobs())
        emit globalProgress(100);
}

void JobQueueData::onFinishedThread()
{
    //qDebug() << "JobQueueData::onFinishedThread()";
    QThread *thread = qobject_cast<QThread *>(sender());
    assignForDeletion(thread);
}

void JobQueueData::onProgressUpdate()
{
    qDebug() << "JobQueueData::onProgressUpdate()";
    JobRunner *runner = qobject_cast<JobRunner *>(sender());
    Q_ASSERT(runner);
    JobItem *jobItem = m_jobModel->getJobItemForIdentifier(runner->getIdentifier());
    jobItem->setProgress(runner->getProgress());
    updateGlobalProgress();
}

// estimates global progress from the progress of multiple running jobs
void JobQueueData::updateGlobalProgress()
{
    qDebug() << "JobQueueData::updateGlobalProgress()";
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
    for(QMap<QString, QThread *>::iterator it=m_threads.begin(); it!=m_threads.end(); ++it) {
        if(it.value() == thread) {
            thread->deleteLater();
            m_threads.erase(it);
            return;
        }
    }
    throw GUIHelpers::Error("JobQueueData::assignForDeletion() -> Error! Can't find thread.");
}

//! Removes JobRunner from the map of known runners, assigns it for deletion.
void JobQueueData::assignForDeletion(JobRunner *runner)
{
    qDebug() << "JobQueueData::assignForDeletion(JobRunner)";
    Q_ASSERT(runner);
    runner->disconnect();
    for(QMap<QString, JobRunner *>::iterator it=m_runners.begin(); it!=m_runners.end(); ++it) {
        if(it.value() == runner) {
            qDebug() << "       JobQueueData::assignForDeletion(JobRunner) -> deleting runner";
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
