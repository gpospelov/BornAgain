#include "JobQueueItem.h"
#include "JobQueueModel.h"
#include "JobItem.h"
#include "OutputDataItem.h"
#include "GUIHelpers.h"
#include <QXmlStreamWriter>
#include <QDebug>
#include <QTimer>
#include <QThread>

JobQueueItem::JobQueueItem(QString name)
    : m_name(name)
    , m_progress(0)
{
    m_data_items.append(new OutputDataItem());

//    mp_job_watcher = new QFutureWatcher<void>;
//    connect(mp_job_watcher, SIGNAL(finished()), this, SLOT(onJobFinished()));

//    m_jobItem = new JobItem();

}


JobQueueItem::~JobQueueItem()
{
    clear();
}



//void JobQueueItem::run()
//{
//    qDebug() << "JobQueueItem::run(): preparing to run a thread";
//    JobItem *jobItem = new JobItem();
//    QThread *thread = new QThread();
//    jobItem->moveToThread(thread);

//    // thread will start jobItem::run
//    connect(thread, SIGNAL(started()), jobItem, SLOT(run()));

//    // thread will quit after JobItem is done
//    connect(jobItem, SIGNAL(finished()), thread, SLOT(quit()));
//    connect(jobItem, SIGNAL(finished()), this, SLOT(onJobFinished()));

//    // objects will be deleted after JobItem is done
//    connect(jobItem, SIGNAL(finished()), jobItem, SLOT(deleteLater()));
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

//    qDebug() << "JobQueueItem::run(): starting thread";
//    thread->start();
//    qDebug() << "JobQueueItem::run(): thread is started";

//}


void JobQueueItem::onJobFinished()
{
    qDebug() << "JobQueueItem::onJobFinished()";
}


//void JobQueueItem::loopFunctionWithDelay()
//{
//    qDebug() << "JobQueueItem::loopFunctionWithDelay()" << m_counterForDelayedLoop;
//    if(m_counterForDelayedLoop < 100) {
//        m_counterForDelayedLoop++;
//        qDebug() << "XXX1";
//        QTimer::singleShot(5000, this, SLOT(loopFunctionWithDelay()));
//        qDebug() << "XXX2";
//    }

//}

// --------------------


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


