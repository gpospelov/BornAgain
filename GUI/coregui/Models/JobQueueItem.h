#ifndef JOBQUEUEITEM_H
#define JOBQUEUEITEM_H

#include <QString>

//! Simple JobQueueItem with name and jobId which is handled by JobQueueModel
//!
//! See also JobItem which contains real information about the job.
class JobQueueItem
{
public:
    JobQueueItem(QString identifier) : m_identifier(identifier){}

    QString getIdentifier() const { return m_identifier; }
    void setIdentifier(QString identifier) { m_identifier = identifier; }

private:
    QString m_identifier;
};


#endif
