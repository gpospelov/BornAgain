#include "OutputDataItem.h"
#include "JobQueueModel.h"
#include "GUIHelpers.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

OutputDataItem::OutputDataItem()
    : m_data(0)
    , m_name("DefaultName")
    , m_xaxis_min(0.0)
    , m_xaxis_max(0.0)
    , m_yaxis_min(0.0)
    , m_yaxis_max(0.0)
    , m_zaxis_min(0.0)
    , m_zaxis_max(0.0)
    , m_is_logz(true)
    , m_is_interpolated(true)
{

}


void OutputDataItem::writeTo(QXmlStreamWriter *writer)
{
    Q_ASSERT(writer);
    writer->writeStartElement(JobQueueXML::OutputDataTag);
    writer->writeAttribute(JobQueueXML::OutputDataNameAttribute, getName());
    writer->writeAttribute(JobQueueXML::OutputDataXminAttribute, QString::number(getXaxisMin()));
    writer->writeAttribute(JobQueueXML::OutputDataXmaxAttribute, QString::number(getXaxisMax()));
    writer->writeAttribute(JobQueueXML::OutputDataYminAttribute, QString::number(getYaxisMin()));
    writer->writeAttribute(JobQueueXML::OutputDataYmaxAttribute, QString::number(getYaxisMax()));
    writer->writeAttribute(JobQueueXML::OutputDataZminAttribute, QString::number(getZaxisMin()));
    writer->writeAttribute(JobQueueXML::OutputDataZmaxAttribute, QString::number(getZaxisMax()));
    writer->writeAttribute(JobQueueXML::OutputDataLogzAttribute, QString::number(isLogz()));
    writer->writeAttribute(JobQueueXML::OutputDataInterpolatedAttribute, QString::number(isInterpolated()));
    writer->writeEndElement(); // OutputDataTag

}


void OutputDataItem::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);
    qDebug() << "OutputDataItem::readFrom() -> " << reader->name();
    if(reader->name() != JobQueueXML::OutputDataTag) {
        throw GUIHelpers::Error("OutputDataItem::readFrom() -> Format error in p1");
    }

    setName(reader->attributes()
            .value(JobQueueXML::OutputDataNameAttribute).toString());

    setXaxisMin(reader->attributes()
            .value(JobQueueXML::OutputDataXminAttribute).toDouble());

    setXaxisMax(reader->attributes()
            .value(JobQueueXML::OutputDataXmaxAttribute).toDouble());

    setYaxisMin(reader->attributes()
            .value(JobQueueXML::OutputDataYminAttribute).toDouble());

    setYaxisMax(reader->attributes()
            .value(JobQueueXML::OutputDataYmaxAttribute).toDouble());

    setZaxisMin(reader->attributes()
            .value(JobQueueXML::OutputDataZminAttribute).toDouble());

    setZaxisMax(reader->attributes()
            .value(JobQueueXML::OutputDataZmaxAttribute).toDouble());

    setLogz(reader->attributes()
            .value(JobQueueXML::OutputDataLogzAttribute).toInt());

    setInterpolated(reader->attributes()
            .value(JobQueueXML::OutputDataInterpolatedAttribute).toInt());

}
