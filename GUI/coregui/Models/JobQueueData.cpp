#include "JobQueueData.h"
#include "JobQueueItem.h"
#include "JobItem.h"
#include "JobRunner.h"
#include "GUIHelpers.h"
#include <QUuid>
#include <QThread>
#include <QDateTime>
#include <QDebug>


int JobQueueData::m_job_index = 0;

//! Creates JobQueueItem and corresponding JobItem.
//! Created JobItem will be registered using unique identifier.
JobQueueItem *JobQueueData::createJobQueueItem(QString jobName, Simulation *simulation)
{
    JobQueueItem *result = new JobQueueItem(generateJobIdentifier());
    if(jobName.isEmpty()) jobName = generateJobName();
    m_job_items[result->getIdentifier()] = new JobItem(jobName);
    if(simulation) m_simulations[result->getIdentifier()] = simulation;
    return result;
}


//! returns existing JobItem for given identifier
const JobItem *JobQueueData::getJobItem(QString identifier) const
{
    QMap<QString, JobItem *>::const_iterator it = m_job_items.find(identifier);
    if(it != m_job_items.end()) {
        return it.value();
    }
    throw GUIHelpers::Error("JobQueueData::getJobItem() -> Error! Can't find item."+identifier);
    return 0;
}

//! returns existing JobItem for given identifier (const version)
JobItem *JobQueueData::getJobItem(QString identifier)
{
    return const_cast<JobItem *>(static_cast<const JobQueueData &>(*this).getJobItem(identifier));
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
Simulation *JobQueueData::getSimulation(QString identifier)
{
    QMap<QString, Simulation *>::const_iterator it = m_simulations.find(identifier);
    if(it != m_simulations.end()) {
        return it.value();
    }
    return 0;
}


//! returns identifier for given JobIteM
QString JobQueueData::getIdentifierForJobItem(const JobItem *item)
{
    for(QMap<QString, JobItem *>::iterator it=m_job_items.begin(); it!=m_job_items.end(); ++it) {
        if(it.value() == item) return it.key();
    }
    throw GUIHelpers::Error("JobQueueData::getIdentifierForJobItem() -> Error! Can't find item.");
}


//! submit job and run it in a thread
void JobQueueData::runJob(QString identifier)
{
    if(getThread(identifier)) {
        qDebug() << "JobQueueData::runInThread() -> Thread is already running";
        return;
    }

    JobRunner *runner = new JobRunner(identifier, getSimulation(identifier));
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
void JobQueueData::cancelJob(QString identifier)
{
    qDebug() << "JobQueueData::cancelJob()";
    if(QThread *thread = getThread(identifier)) {
        thread->quit();
        JobItem *jobItem = getJobItem(identifier);
        jobItem->setStatus(JobItem::Canceled);
        jobItem->setEndTime(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
        jobItem->setProgress(0);
        JobRunner *runner = getRunner(identifier);
        runner->disconnect();
        assignForDeletion(runner);
        updateGlobalProgress();
        return;
    }
    qDebug() << "JobQueueData::cancelJob() -> No thread is running";
}


//! remove job from list completely
void JobQueueData::removeJob(QString identifier)
{
    qDebug() << "JobQueueData::removeJob";
    cancelJob(identifier);
    for(QMap<QString, JobItem *>::iterator it=m_job_items.begin(); it!=m_job_items.end(); ++it) {
        if(it.key() == identifier) {
            delete it.value();
            m_job_items.erase(it);
            return;
        }
    }
}


void JobQueueData::onStartedJob()
{
    qDebug() << "JobQueueData::onStartedJob()";
    JobRunner *runner = qobject_cast<JobRunner *>(sender());
    Q_ASSERT(runner);
    JobItem *jobItem = getJobItem(runner->getIdentifier());
    jobItem->setProgress(0);
    jobItem->setStatus(JobItem::Running);
    QString begin_time = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    jobItem->setBeginTime(begin_time);
    jobItem->setEndTime("");
}


void JobQueueData::onFinishedJob()
{
    qDebug() << "JobQueueData::onFinishedJob()";
    JobRunner *runner = qobject_cast<JobRunner *>(sender());
    Q_ASSERT(runner);
    JobItem *jobItem = getJobItem(runner->getIdentifier());
    jobItem->setStatus(JobItem::Completed);
    QString end_time = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    jobItem->setEndTime(end_time);

    // I tell to the thread to exit here (instead of connecting JobRunner::finished to the QThread::quit because of strange behaviour)
    getThread(runner->getIdentifier())->quit();

    assignForDeletion(runner);
}


void JobQueueData::onFinishedThread()
{
    qDebug() << "JobQueueData::onFinishedThread()";
    QThread *thread = qobject_cast<QThread *>(sender());
    assignForDeletion(thread);
}


void JobQueueData::onProgressUpdate()
{
    qDebug() << "JobQueueData::ProgressUpdate()";
    JobRunner *runner = qobject_cast<JobRunner *>(sender());
    Q_ASSERT(runner);
    JobItem *jobItem = getJobItem(runner->getIdentifier());
    jobItem->setProgress(runner->getProgress());
    updateGlobalProgress();
}


void JobQueueData::updateGlobalProgress()
{
    int global_progress(0);
    int nRunningJobs(0);
    for(QMap<QString, JobItem *>::iterator it = m_job_items.begin(); it!= m_job_items.end(); ++it) {
        JobItem *jobItem = it.value();
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
    Q_ASSERT(runner);
    for(QMap<QString, JobRunner *>::iterator it=m_runners.begin(); it!=m_runners.end(); ++it) {
        if(it.value() == runner) {
            runner->deleteLater();
            m_runners.erase(it);
            return;
        }
    }
    throw GUIHelpers::Error("JobQueueData::assignForDeletion() -> Error! Can't find the runner.");
}


//! generates job name
QString JobQueueData::generateJobName()
{
    return QString("job")+QString::number(++m_job_index);
}


//! generate unique job identifier
QString JobQueueData::generateJobIdentifier()
{
    return QUuid::createUuid().toString();
}

