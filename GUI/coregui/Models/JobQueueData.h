#ifndef JOBQUEUEDATA_H
#define JOBQUEUEDATA_H

#include <QObject>
#include <QString>
#include <QMap>

class JobItem;
class JobQueueItem;
class Simulation;
class JobRunner;

class QThread;

//! Holds correspondance of job identifiers and JobItem's, QThread's etc
//! Contains all submit/cancel logic
class JobQueueData : public QObject
{
    Q_OBJECT
public:

    JobQueueItem *createJobQueueItem(Simulation *simulation = 0);

    const JobItem *getJobItem(QString identifier) const;
    JobItem *getJobItem(QString identifier);

    QThread *getThread(QString identifier);

    JobRunner *getRunner(QString identifier);

    QString getIdentifierForJobItem(const JobItem *);

public slots:
    void onSubmitJob(QString identifier);
    void onCancelJob(QString identifier);
    void onStartedJob();
    void onProgressUpdate();
    void onFinishedJob();
    void onFinishedThread();

private:
    void assignForDeletion(QThread *thread);
    void assignForDeletion(JobRunner *runner);

    QString generateJobName();
    QString generateJobIdentifier();

    QMap<QString, JobItem *> m_job_items; //!< correspondance of JobIdentifier and JobItem's
    QMap<QString, QThread *> m_threads; //! correspondance of JobIdentifier and running threads
    QMap<QString, JobRunner *> m_runners; //! correspondance of JobIdentifier and JobRunner's

    static int m_job_index;
};


#endif
