// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobWorker.cpp
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
#include "item_constants.h"
#include <QDateTime>
#include <QDebug>
#include <memory>

JobWorker::JobWorker(QString identifier, GISASSimulation *simulation)
    : m_identifier(identifier)
    , m_simulation(simulation)
    , m_percentage_done(0)
    , m_job_status(Constants::STATUS_IDLE)
    , m_terminate_request_flag(false)
    , m_simulation_duration(0)
{
}

void JobWorker::start()
{
    qDebug() << "JobRunner::start() " << m_simulation;
    m_terminate_request_flag = false;
    m_simulation_duration = 0;
    emit started();

    if(m_simulation) {
        m_simulation->subscribe(
            [this] (int percentage_done) {
                return simulationInformsUs(percentage_done); } );

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
            m_percentage_done = 100;
            m_failure_message = QString(
                        "JobRunner::start() -> Simulation failed with exception throw:\n\n");

            m_failure_message.append(QString(ex.what()));
        }

    } else {
        m_job_status = Constants::STATUS_FAILED;
        m_percentage_done = 100;
        m_failure_message = QString("JobRunner::start() -> Error. Simulation doesn't exist.");
    }
    emit progressUpdate();
    emit finished();
}

//! Informs us about progress of the simulation. Returns true if we want to continue the simulation.
//! To be registered as callback function via ProgressHandler::subscribe().
bool JobWorker::simulationInformsUs(int percentage_done)
{
    if (percentage_done > m_percentage_done) {
        m_percentage_done = percentage_done;
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
