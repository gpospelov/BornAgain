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

#include <QObject>
#include <QString>
#include <QMap>

//class JobItem;
class NJobItem;
class NJobModel;
//class JobQueueItem;
class Simulation;
class JobRunner;
class QThread;


//! Main class to run jobs
class BA_CORE_API_ JobQueueData : public QObject
{
    Q_OBJECT
public:
    JobQueueData(NJobModel *jobModel);

    QThread *getThread(QString identifier);
    JobRunner *getRunner(QString identifier);
    Simulation *getSimulation(QString identifier);

    bool hasUnfinishedJobs();

    void setResults(NJobItem *jobItem, const Simulation *simulation);

signals:
    void globalProgress(int);
    void focusRequest(const QString &identifier);
    void jobIsFinished(const QString &identifier);

public slots:
    void onStartedJob();
    void onProgressUpdate();
    void onFinishedJob();
    void onFinishedThread();
    void onCancelAllJobs();

    void runJob(const QString &identifier);
    void runJob(NJobItem *jobItem);
    void cancelJob(const QString &identifier);
    void removeJob(const QString &identifier);

private:
    void assignForDeletion(QThread *thread);
    void assignForDeletion(JobRunner *runner);
    void clearSimulation(const QString &identifier);

    void updateGlobalProgress();

//    QString generateJobName();
//    QString generateJobIdentifier();

//    QMap<QString, JobItem *> m_job_items; //!< correspondance of JobIdentifier and JobItem's
    QMap<QString, QThread *> m_threads; //! correspondance of JobIdentifier and running threads
    QMap<QString, JobRunner *> m_runners; //! correspondance of JobIdentifier and JobRunner's
    QMap<QString, Simulation *> m_simulations; //! correspondance of JobIdentifier and simulation

    NJobModel *m_jobModel;
};


#endif
