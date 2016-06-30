// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobWorker.cpp
//! @brief     Implements class JobWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobWorker.h"
#include "GISASSimulation.h"
#include "ProgressHandler.h"
#include "ThreadInfo.h"
#include "item_constants.h"
#include <functional>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

JobWorker::JobWorker(QString identifier, GISASSimulation *simulation)
    : m_identifier(identifier)
    , m_simulation(simulation)
    , m_progress(0)
    , m_job_status(Constants::STATUS_IDLE)
    , m_terminate_request_flag(false)
    , m_simulation_duration(0)
{

}

int JobWorker::getProgress() const
{
    // sometimes simulation underestimate the number of iterations required
    // and progress can be greater than 100
    return m_progress < 100 ? m_progress : 100;
}

void JobWorker::start()
{
    qDebug() << "JobRunner::start() " << m_simulation;
    m_terminate_request_flag = false;
    m_simulation_duration = 0;
    emit started();

    if(m_simulation) {
        ProgressHandler_t progressHandler(new ProgressHandler());
        ProgressHandler::Callback_t callback = [this] (int n) {
            return simulationProgressCallback(n);
        };
        progressHandler->setCallback(callback);
        m_simulation->setProgressHandler(progressHandler);

        m_job_status = Constants::STATUS_RUNNING;

        try {
            QDateTime beginTime = QDateTime::currentDateTime();
            m_simulation->runSimulation();
            if(m_job_status != Constants::STATUS_CANCELED)
                m_job_status = Constants::STATUS_COMPLETED;

            QDateTime endTime = QDateTime::currentDateTime();
            m_simulation_duration = beginTime.msecsTo(endTime);

        }
        catch(const std::exception &ex)
        {
            m_job_status = Constants::STATUS_FAILED;
            m_progress=100;
            m_failure_message = QString(
                        "JobRunner::start() -> Simulation failed with exception throw:\n\n");

            m_failure_message.append(QString(ex.what()));
        }

    } else {
        m_job_status = Constants::STATUS_FAILED;
        m_progress=100;
        m_failure_message = QString("JobRunner::start() -> Error. Simulation doesn't exist.");
    }
    emit progressUpdate();
    emit finished();
}

//! function which is called by the simulation to report its progress
bool JobWorker::simulationProgressCallback(int progress)
{
    if(progress >= m_progress) {
        m_progress = progress;
        emit progressUpdate();
    }

    return !m_terminate_request_flag;
}

//! set request for JobRunner to terminate underlying domain simulation
void JobWorker::terminate()
{
    qDebug() << "JobRunner::terminate()";
    m_terminate_request_flag = true;
    m_job_status = Constants::STATUS_CANCELED;
}
