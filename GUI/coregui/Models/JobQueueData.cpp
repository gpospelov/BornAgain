#include "JobQueueData.h"
#include "JobQueueItem.h"
#include "JobItem.h"
#include "GUIHelpers.h"
#include <QUuid>


int JobQueueData::m_job_index = 0;



//JobItem *JobQueueData::getJobItem(QString identifier)
//{
//    QMap<QString, JobItem *>::iterator it = m_job_items.find(identifier);
//    if(it != m_job_items.end()) {
//        return it.value();
//    }
//    return 0;
//}

const JobItem *JobQueueData::getJobItem(QString identifier) const
{
    QMap<QString, JobItem *>::const_iterator it = m_job_items.find(identifier);
    if(it != m_job_items.end()) {
        return it.value();
    }
    throw GUIHelpers::Error("JobQueueData::getJobItem() -> Error! Can't find item.");
    return 0;
}

JobItem *JobQueueData::getJobItem(QString identifier)
{
    return const_cast<JobItem *>(static_cast<const JobQueueData &>(*this).getJobItem(identifier));
}



JobQueueItem *JobQueueData::createJobQueueItem(Simulation *simulation)
{
    (void)simulation;
    JobQueueItem *result = new JobQueueItem(generateJobName(), generateJobIdentifier());

    m_job_items[result->getIdentifier()] = new JobItem(result->getName());

    return result;
}

QString JobQueueData::generateJobName()
{
    return QString("job")+QString::number(++m_job_index);
}


QString JobQueueData::generateJobIdentifier()
{
    return QUuid::createUuid().toString();
}
