// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobWorker.h
//! @brief     Defines class JobWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBWORKER_H
#define JOBWORKER_H

#include "WinDllMacros.h"
#include <QObject>

class GISASSimulation;

//! The JobWorker class provides running the domain simulation in a thread.

class BA_CORE_API_ JobWorker : public QObject
{
    Q_OBJECT
public:

    JobWorker(QString identifier, GISASSimulation *simulation = 0);

    QString getIdentifier() const { return m_identifier; }
    void setIdentifier(QString identifier) { m_identifier = identifier; }

    int getProgress() const { return m_percentage_done; }

    bool simulationInformsUs(int);

    bool isTerminated() { return m_terminate_request_flag; }

    QString getStatus() const { return m_job_status; }

    QString getFailureMessage() const { return m_failure_message; }

    int getSimulationDuration() const { return m_simulation_duration; }

signals:
    void started();
    void finished();
    void progressUpdate();

public slots:
    void start();
    void terminate();

private:
    QString m_identifier;
    GISASSimulation *m_simulation;
    int m_percentage_done;
    QString m_job_status;
    bool m_terminate_request_flag;
    QString m_failure_message;
    int m_simulation_duration;
};

#endif // JOBWORKER_H
