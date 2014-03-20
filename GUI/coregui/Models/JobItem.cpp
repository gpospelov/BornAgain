#include "JobItem.h"
#include "JobQueueModel.h"
#include "JobRunner.h"
#include "OutputDataItem.h"
#include "GUIHelpers.h"
#include <QXmlStreamWriter>
#include <QDebug>
#include <QTimer>
#include <QThread>


JobItem::JobItem(QString name)
    : m_name(name)
    , m_status(Idle)
    , m_progress(0)
{
    m_data_items.append(new OutputDataItem());
    m_status_list << "" << "running" << "completed" << "canceled";
}


JobItem::~JobItem()
{
    clear();
}


void JobItem::clear()
{
    qDeleteAll(m_data_items);
    m_data_items.clear();
}


QString JobItem::getStatusString() const
{
    return m_status_list.at(int(m_status));
}


OutputDataItem *JobItem::getOutputDataItem(int n_item)
{
    if(m_data_items.empty() || n_item < 0 || n_item >= m_data_items.size())
        return 0;
    return m_data_items.at(n_item);
}


void JobItem::writeTo(QXmlStreamWriter *writer)
{
    Q_ASSERT(writer);
    writer->writeStartElement(JobQueueXML::JobTag);
    writer->writeAttribute(JobQueueXML::JobNameAttribute, getName());
    writer->writeAttribute(JobQueueXML::JobStatusAttribute, QString::number((int)getStatus()));
    writer->writeAttribute(JobQueueXML::JobBeginTimeAttribute, getBeginTime());
    writer->writeAttribute(JobQueueXML::JobEndTimeAttribute, getEndTime());
    writer->writeAttribute(JobQueueXML::JobCommentsAttribute, getComments());
    foreach(OutputDataItem *item, m_data_items) {
        item->writeTo(writer);
    }
    writer->writeEndElement(); // JobTag
}


void JobItem::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);
    clear();

    qDebug() << "JobQueueItem::readFrom() -> " << reader->name();
    if(reader->name() != JobQueueXML::JobTag) {
        throw GUIHelpers::Error("JobQueueItem::readFrom() -> Format error in p1");
    }

    setName(reader->attributes()
            .value(JobQueueXML::JobNameAttribute).toString());

    setBeginTime(reader->attributes()
            .value(JobQueueXML::JobBeginTimeAttribute).toString());

    setEndTime(reader->attributes()
            .value(JobQueueXML::JobEndTimeAttribute).toString());

    setComments(reader->attributes()
            .value(JobQueueXML::JobCommentsAttribute).toString());

    JobStatus status = (JobStatus) (reader->attributes()
            .value(JobQueueXML::JobStatusAttribute).toInt());
    setStatus(status);


    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {

            if (reader->name() == JobQueueXML::OutputDataTag) {
                qDebug() << "XXX output data";
                OutputDataItem *item = new OutputDataItem();
                item->readFrom(reader);
                m_data_items.append(item);
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == JobQueueXML::JobTag) {
                break; // end of xml of current Job
            }
        }
    }

}


