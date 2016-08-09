// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobQueueData.h
//! @brief     Defines class JobQueueData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBQUEUEDATA_H
#define JOBQUEUEDATA_H

#include "WinDllMacros.h"
#include <QMap>
#include <QObject>

class JobItem;
class JobModel;
class GISASSimulation;
class JobWorker;

//! The JobQueueData class holds all objects/logic to run simulation in a thread.

class BA_CORE_API_ JobQueueData : public QObject
{
    Q_OBJECT
public:
    JobQueueData(JobModel *jobModel);

    QThread *getThread(QString identifier);
    JobWorker *getRunner(QString identifier);
    GISASSimulation *getSimulation(QString identifier);

    bool hasUnfinishedJobs();

signals:
    void globalProgress(int);
    void focusRequest(JobItem *jobItem);

public slots:
    void onStartedJob();
    void onProgressUpdate();
    void onFinishedJob();

    void onFinishedThread();
    void onCancelAllJobs();

    void runJob(JobItem *jobItem);
    void cancelJob(const QString &identifier);
    void removeJob(const QString &identifier);

private:
    void assignForDeletion(QThread *thread);
    void assignForDeletion(JobWorker *runner);
    void clearSimulation(const QString &identifier);
    void processFinishedJob(JobWorker *runner, JobItem *jobItem);

    void updateGlobalProgress();

    QMap<QString, QThread *> m_threads; //! correspondance of JobIdentifier and running threads
    QMap<QString, JobWorker *> m_runners; //! correspondance of JobIdentifier and JobRunner's
    QMap<QString, GISASSimulation *> m_simulations; //! correspondance of JobIdentifier and simulation

    JobModel *m_jobModel;
};

#endif // JOBQUEUEDATA_H
