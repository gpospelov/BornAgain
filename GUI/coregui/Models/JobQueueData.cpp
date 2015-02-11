// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobQueueData.cpp
//! @brief     Implements class JobQueueData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobQueueData.h"
#include "JobQueueItem.h"
#include "OutputDataItem.h"
#include "Simulation.h"
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

//QString JobQueueData::createJob(QString jobName, Simulation *simulation, JobItem::ERunPolicy run_policy)
//{
//    QString identifier = generateJobIdentifier();

//    if(jobName.isEmpty()) jobName = generateJobName();
//    JobItem *jobItem = new JobItem(jobName);
//    jobItem->setRunPolicy(run_policy);
//    m_job_items[identifier] = jobItem;
//    if(simulation) m_simulations[identifier] = simulation;
//    return identifier;
//}


//QString JobQueueData::createJob(JobItem *jobItem)
//{
//    QString identifier = generateJobIdentifier();
//    if(jobItem->getName().isEmpty())
//        jobItem->setName(generateJobName());

//    m_job_items[identifier] = jobItem;
//    return identifier;
//}


//! returns existing JobItem for given identifier
//const JobItem *JobQueueData::getJobItem(QString identifier) const
//{
//    QMap<QString, JobItem *>::const_iterator it = m_job_items.find(identifier);
//    if(it != m_job_items.end()) {
//        return it.value();
//    }
//    throw GUIHelpers::Error("JobQueueData::getJobItem() -> Error! Can't find item."+identifier);
//    return 0;
//}

////! returns existing JobItem for given identifier (const version)
//JobItem *JobQueueData::getJobItem(QString identifier)
//{
//    return const_cast<JobItem *>(static_cast<const JobQueueData &>(*this).getJobItem(identifier));
//}


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
Simulation *JobQueueData::getSimulation(QString identifier)
{
    QMap<QString, Simulation *>::const_iterator it = m_simulations.find(identifier);
    if(it != m_simulations.end()) {
        return it.value();
    }
    return 0;
}


//! returns identifier for given JobIteM
//QString JobQueueData::getIdentifierForJobItem(const JobItem *item)
//{
//    for(QMap<QString, JobItem *>::iterator it=m_job_items.begin(); it!=m_job_items.end(); ++it) {
//        if(it.value() == item) return it.key();
//    }
//    throw GUIHelpers::Error("JobQueueData::getIdentifierForJobItem() -> Error! Can't find item.");
//}

bool JobQueueData::hasUnfinishedJobs()
{
    return m_simulations.size();
}

void JobQueueData::setResults(JobItem *jobItem, const Simulation *simulation)
{
    qDebug() << "JobQueueData::setResults(NJobItem *jobItem, const Simulation *simulation)";
    if(!simulation)
        throw GUIHelpers::Error("NJobItem::setResults() -> Error. Null simulation.");

    IntensityDataItem *intensityItem = jobItem->getIntensityDataItem();

    if(!intensityItem) {
        intensityItem = static_cast<IntensityDataItem *>(m_jobModel->insertNewItem(Constants::IntensityDataType, m_jobModel->indexOfItem(jobItem)));
    }

    // propagatind angle units to OutputDataItem
    if(jobItem->getInstrumentModel()) {
        InstrumentItem *instrumentItem = dynamic_cast<InstrumentItem *>(jobItem->getInstrumentModel()->getInstrumentMap().begin().value());
        qDebug() << instrumentItem->modelType();
        Q_ASSERT(instrumentItem);
        DetectorItem *detectorItem = instrumentItem->getDetectorItem();
        Q_ASSERT(detectorItem);
        ParameterizedItem *subDetector = detectorItem->getSubItems()[DetectorItem::P_DETECTOR];
        Q_ASSERT(subDetector);

        if (subDetector->modelType() == Constants::PhiAlphaDetectorType) {
            AngleProperty angle_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_AXES_UNITS).value<AngleProperty>();
            intensityItem->setRegisteredProperty(IntensityDataItem::P_AXES_UNITS, angle_property.getVariant());
//            if(angle_property.inDegrees())
//                intensityItem->setAxesUnits(Constants::UnitsDegrees);
        }

    }

    qDebug() << "JobItem::setResults()" << intensityItem;

    intensityItem->setItemName(QString("data_%1_%2.int").arg(jobItem->itemName(), QString::number(0)));
    intensityItem->setOutputData(simulation->getIntensityData());
}




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

    Simulation *simulation(0);
    try{
        simulation = DomainSimulationBuilder::getSimulation(jobItem->getSampleModel(), jobItem->getInstrumentModel());

    } catch(const std::exception &ex) {
        jobItem->setStatus(Constants::STATUS_FAILED);
        jobItem->setProgress(100);
        QString message("JobQueueData::runJob() -> Error. Attempt to create sample/instrument object from user description "
                        "has failed with following error message.\n");
        message += QString(ex.what());
        jobItem->setComments(message);
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
    // removing jobs
//    for(QMap<QString, JobItem *>::iterator it=m_job_items.begin(); it!=m_job_items.end(); ++it) {
//        if(it.key() == identifier) {
//            delete it.value();
//            qDebug() << "       JobQueueData::removeJob   removing job" << identifier;
//            m_job_items.erase(it);
//            break;
//        }
//    }
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

    // propagating simulation results
    Simulation *simulation = getSimulation(runner->getIdentifier());
    setResults(jobItem, simulation);

    // propagating status of runner
    jobItem->setStatus(runner->getStatus());
    if(jobItem->isFailed())
        jobItem->setComments(runner->getFailureMessage());

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
    Simulation *simulation = getSimulation(identifier);
    m_simulations.remove(identifier);
    delete simulation;
}


//! generates job name
//QString JobQueueData::generateJobName()
//{
//    m_job_index = 0;
//    for(QMap<QString, JobItem *>::iterator it=m_job_items.begin(); it!=m_job_items.end(); ++it) {
//        QString jobName = it.value()->getName();
//        if(jobName.startsWith("job")) {
//            int job_index = jobName.remove(0,3).toInt();
//            if(job_index > m_job_index) m_job_index = job_index;
//        }
//    }

//    return QString("job")+QString::number(++m_job_index);
//}


////! generate unique job identifier
//QString JobQueueData::generateJobIdentifier()
//{
//    return QUuid::createUuid().toString();
//}

