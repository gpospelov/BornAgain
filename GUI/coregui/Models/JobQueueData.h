#ifndef JOBQUEUEDATA_H
#define JOBQUEUEDATA_H

#include <QString>
#include <QMap>

class JobItem;
class JobQueueItem;
class Simulation;


//! Holds correspondance of job identifiers and JobItem's, QThread's etc
class JobQueueData
{
public:

    JobQueueItem *createJobQueueItem(Simulation *simulation = 0);

    const JobItem *getJobItem(QString identifier) const;
    JobItem *getJobItem(QString identifier);

private:
    QString generateJobName();
    QString generateJobIdentifier();

    static int m_job_index;

    QMap<QString, JobItem *> m_job_items; //!< correspondance of identifier and JobItem's
};


#endif
