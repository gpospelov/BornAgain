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
    , m_xaxis_title("x-axis")
    , m_yaxis_title("y-axis")
{

}

OutputDataItem::~OutputDataItem()
{
    qDebug() << "OutputDataItem::~OutputDataItem()" << this;
}


void OutputDataItem::setOutputData(OutputData<double> *data)
{
    if(data != m_data) {
        qDebug() << "OutputDataItem::setOutputData(OutputData<double> *data)";
        delete m_data;
        m_data = data;
        emit modified();
    }
}


void OutputDataItem::setName(QString name)
{
    if(m_name != name) {
        m_name = name;
        emit modified();
    }
}

void OutputDataItem::setXaxisMin(double xmin)
{
    if(m_xaxis_min != xmin) {
        m_xaxis_min = xmin;
        emit modified();
    }
}

void OutputDataItem::setXaxisMax(double xmax)
{
    if(m_xaxis_max == xmax) {
        m_xaxis_max = xmax;
        emit modified();
    }
}

void OutputDataItem::setYaxisMin(double ymin)
{
    if(m_yaxis_min != ymin) {
        m_yaxis_min = ymin;
        emit modified();
    }
}

void OutputDataItem::setYaxisMax(double ymax)
{
    if(m_yaxis_max != ymax) {
        m_yaxis_max = ymax;
        emit modified();
    }
}

void OutputDataItem::setZaxisMin(double zmin)
{
    if(m_zaxis_min != zmin) {
        m_zaxis_min = zmin;
        emit modified();
    }
}


void OutputDataItem::setZaxisMax(double zmax)
{
    if(m_zaxis_max != zmax) {
        m_zaxis_max = zmax;
        emit modified();
    }
}

void OutputDataItem::setZaxisRange(double zmin, double zmax)
{
    if(m_zaxis_min != zmin || m_zaxis_max != zmax) {
        m_zaxis_min = zmin;
        m_zaxis_max = zmax;
        emit modified();
    }
}


void OutputDataItem::setLogz(bool logz)
{
    if(m_is_logz != logz) {
        m_is_logz = logz;
        emit modified();
    }
}

void OutputDataItem::setInterpolated(bool interp)
{
    if(m_is_interpolated != interp) {
        m_is_interpolated = interp;
        emit modified();
    }
}

void OutputDataItem::setXaxisTitle(QString xtitle)
{
    if(m_xaxis_title != xtitle) {
        m_xaxis_title = xtitle;
        emit modified();
    }
}

void OutputDataItem::setYaxisTitle(QString ytitle)
{
    if(m_yaxis_title != ytitle) {
        m_yaxis_title = ytitle;
        emit modified();
    }
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
    writer->writeAttribute(JobQueueXML::OutputDataXtitleAttribute, getXaxisTitle());
    writer->writeAttribute(JobQueueXML::OutputDataYtitleAttribute, getYaxisTitle());
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

    setXaxisTitle(reader->attributes()
                  .value(JobQueueXML::OutputDataXtitleAttribute).toString());
    setYaxisTitle(reader->attributes()
                  .value(JobQueueXML::OutputDataYtitleAttribute).toString());

}
