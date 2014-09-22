#include "JobRunner.h"
#include "Simulation.h"
#include "ProgressHandler.h"
#include "ThreadInfo.h"
#include <boost/bind.hpp>
#include <QTimer>
#include <QDebug>


JobRunner::JobRunner(QString identifier, Simulation *simulation)
    : m_identifier(identifier)
    , m_simulation(simulation)
    , m_progress(0)
    , m_job_status(JobItem::Idle)
    , m_terminate_request_flag(false)
{

}


JobRunner::~JobRunner()
{
    qDebug() << "JobRunner::~JobRunner()";
}


int JobRunner::getProgress() const
{
    // sometimes simulation underestimate the number of iterations required
    // and progress can be greater than 100
    return m_progress < 100 ? m_progress : 100;
}


void JobRunner::start()
{
    qDebug() << "JobRunner::start() " << m_simulation;
    m_terminate_request_flag = false;
    emit started();

    if(m_simulation) {
        ProgressHandler_t progressHandler(new ProgressHandler());
        ProgressHandler::Callback_t callback = boost::bind(&JobRunner::similationProgressCallback, this, _1);
        progressHandler->setCallback(callback);
        m_simulation->setProgressHandler(progressHandler);
        //ThreadInfo info;
        //info.n_threads = 8;
        //m_simulation->setThreadInfo(info);

        m_job_status = JobItem::Running;

        try {
            m_simulation->runSimulation();
            if(m_job_status != JobItem::Canceled)
                m_job_status = JobItem::Completed;
        }
        catch(const std::exception &ex)
        {
            m_job_status = JobItem::Failed;
            m_progress=100;
            m_failure_message = QString(ex.what());
        }

        if(m_terminate_request_flag) m_progress=-1;

        emit progressUpdate();
        emit finished();
    } else {
        runFakeSimulation();
    }
}


//! Fake simulation function to mimic some hard work going on
void JobRunner::runFakeSimulation()
{
    qDebug() << "JobItem::runFakeSimulation()" << m_progress;
    if(m_progress < 100) {
        m_progress++;
        emit progressUpdate();
        QTimer::singleShot(100, this, SLOT(runFakeSimulation()));
    }
    if(m_progress >=100 || m_terminate_request_flag) {
        emit progressUpdate();
        emit finished();
    }
}


//! function which is called by the Simulation to report its progress
bool JobRunner::similationProgressCallback(int progress)
{
    m_progress = progress;
    //qDebug() << "JobRunner::getSimilationProgress(int)" << progress;
    emit progressUpdate();
    return !m_terminate_request_flag;
}


void JobRunner::terminate()
{
    qDebug() << "JobRunner::terminate()";
    m_terminate_request_flag = true;
    m_job_status = JobItem::Canceled;
}
