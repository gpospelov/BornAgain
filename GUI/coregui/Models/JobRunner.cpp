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
{

}


JobRunner::~JobRunner()
{
    qDebug() << "JobRunner::~JobRunner()";
}


void JobRunner::start()
{
    qDebug() << "JobRunner::start() " << m_simulation;
    emit started();

    if(m_simulation) {
        ProgressHandler::Callback_t callback = boost::bind(&JobRunner::similationProgressCallback, this, _1);
        m_simulation->setProgressCallback(callback);
//        ThreadInfo info;
//        info.n_threads = 2;
//        m_simulation->setThreadInfo(info);
        m_simulation->runSimulation();
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
        m_progress = m_progress+4;
        emit progressUpdate();
        QTimer::singleShot(500, this, SLOT(runFakeSimulation()));
    }
    if(m_progress >=100) {
        emit progressUpdate();
        emit finished();
    }
}


//! function which is called by the Simulation to report its progress
void JobRunner::similationProgressCallback(int progress)
{
    m_progress = progress;
    qDebug() << "JobRunner::getSimilationProgress(int)" << progress;
    emit progressUpdate();
}


void JobRunner::terminate()
{
    m_progress = 1000;
}
