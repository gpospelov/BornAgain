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

    void runInThread(QString identifier);

    void cancelJob(QString identifier);

public slots:
//    void onFinishedThread();
    void onStartedJob();
    void onFinishedJob();
    void onProgressUpdate();

    void onDestroyedThread();
    void onDestroyedRunner();

private:
    QString generateJobName();
    QString generateJobIdentifier();

//    void deleteThread(QThread *thread);
//    void deleteRunner(JobRunner *runner);

    static int m_job_index;

    QMap<QString, JobItem *> m_job_items; //!< correspondance of JobIdentifier and JobItem's

    QMap<QString, QThread *> m_threads; //! correspondance of JobIdentifier and running threads

    QMap<QString, JobRunner *> m_runners; //! correspondance of JobIdentifier and jobRunner
};


#endif
