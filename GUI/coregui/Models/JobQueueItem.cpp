#include "JobQueueItem.h"
#include "JobQueueModel.h"
#include "OutputDataItem.h"
#include "GUIHelpers.h"
#include <QXmlStreamWriter>
#include <QDebug>

JobQueueItem::JobQueueItem(QString name)
    : m_name(name)
{
    m_data_items.append(new OutputDataItem());
}


JobQueueItem::~JobQueueItem()
{
    clear();
}


void JobQueueItem::clear()
{
    qDeleteAll(m_data_items);
    m_data_items.clear();
}


void JobQueueItem::writeTo(QXmlStreamWriter *writer)
{
    Q_ASSERT(writer);
    writer->writeStartElement(JobQueueXML::JobTag);
    writer->writeAttribute(JobQueueXML::JobNameAttribute, getName());
    writer->writeAttribute(JobQueueXML::JobStatusAttribute, getStatus());
    writer->writeAttribute(JobQueueXML::JobBeginTimeAttribute, getBeginTime());
    writer->writeAttribute(JobQueueXML::JobEndTimeAttribute, getEndTime());
    writer->writeAttribute(JobQueueXML::JobCommentsAttribute, getComments());
    foreach(OutputDataItem *item, m_data_items) {
        item->writeTo(writer);
    }
    writer->writeEndElement(); // JobTag
}


void JobQueueItem::readFrom(QXmlStreamReader *reader)
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

    setStatus(reader->attributes()
            .value(JobQueueXML::JobStatusAttribute).toString());


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


