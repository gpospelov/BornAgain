// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobRunner.h
//! @brief     Defines class JobRunner
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBRUNNER_H
#define JOBRUNNER_H

#include "WinDllMacros.h"
#include "JobItem.h"
#include <QObject>
#include <QString>

class Simulation;

//! Class for running the simulation in a thread
class BA_CORE_API_ JobRunner : public QObject
{
    Q_OBJECT
public:

    JobRunner(QString identifier, Simulation *simulation = 0);
    virtual ~JobRunner();

    QString getIdentifier() const { return m_identifier; }
    void setIdentifier(QString identifier) { m_identifier = identifier; }

    int getProgress() const;

    bool similationProgressCallback(int);

    bool isTerminated() { return m_terminate_request_flag; }

    JobItem::EJobStatus getStatus() const { return m_job_status; }

    QString getFailureMessage() const { return m_failure_message; }

signals:
    void started();
    void finished();
    void progressUpdate();

public slots:
    void start();
    void terminate();

private slots:
    void runFakeSimulation();

private:
    QString m_identifier;
    Simulation *m_simulation;
    int m_progress;
    JobItem::EJobStatus m_job_status;

    bool m_terminate_request_flag;
    QString m_failure_message;
};



#endif // JOBRUNNER_H

