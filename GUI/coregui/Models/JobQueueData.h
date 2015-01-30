// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobQueueData.h
//! @brief     Defines class JobQueueData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBQUEUEDATA_H
#define JOBQUEUEDATA_H

#include "JobItem.h"
#include <QObject>
#include <QString>
#include <QMap>

class JobItem;
class JobQueueItem;
class Simulation;
class JobRunner;
class QThread;


//! Holds correspondance of job identifiers and JobItem, QThread, JobRunner
//! and Simulation objects. Contains all run/cancel/progress logic for job.
class BA_CORE_API_ JobQueueData : public QObject
{
    Q_OBJECT
public:
    JobQueueData();

    QString createJob(QString jobName = QString(), Simulation *simulation = 0, JobItem::ERunPolicy run_policy = JobItem::SUBMIT_ONLY);
    QString createJob(JobItem *jobItem);

    const JobItem *getJobItem(QString identifier) const;
    JobItem *getJobItem(QString identifier);

    QThread *getThread(QString identifier);
    JobRunner *getRunner(QString identifier);
    Simulation *getSimulation(QString identifier);

    QString getIdentifierForJobItem(const JobItem *);

    bool hasUnfinishedJobs();

signals:
    void globalProgress(int);
    void focusRequest(JobItem *item);
    void jobIsFinished(const QString &identifier);

public slots:
    void onStartedJob();
    void onProgressUpdate();
    void onFinishedJob();
    void onFinishedThread();
    void onCancelAllJobs();

    void runJob(const QString &identifier);
    void cancelJob(const QString &identifier);
    void removeJob(const QString &identifier);

private:
    void assignForDeletion(QThread *thread);
    void assignForDeletion(JobRunner *runner);
    void clearSimulation(const QString &identifier);

    void updateGlobalProgress();

    QString generateJobName();
    QString generateJobIdentifier();

    QMap<QString, JobItem *> m_job_items; //!< correspondance of JobIdentifier and JobItem's
    QMap<QString, QThread *> m_threads; //! correspondance of JobIdentifier and running threads
    QMap<QString, JobRunner *> m_runners; //! correspondance of JobIdentifier and JobRunner's
    QMap<QString, Simulation *> m_simulations; //! correspondance of JobIdentifier and simulation

    int m_job_index;
};


#endif
