// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobItem.cpp
//! @brief     Implements class JobItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobItem.h"
#include "JobQueueModel.h"
#include "JobRunner.h"
#include "OutputDataItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "InstrumentItem.h"
#include "GUIHelpers.h"
#include "Simulation.h"
#include "AngleProperty.h"
#include "DetectorItems.h"
#include "InstrumentItem.h"
#include <QXmlStreamWriter>
#include <QDebug>
#include <QTimer>
#include <QThread>


namespace
{
QMap<QString, QString> initializeRunPolicies()
{
    QMap<QString, QString> result;
    result["Immediately"] = QString("Start simulation immediately, switch to Jobs view automatically when completed");
    result["In background"] = QString("Start simulation immediately, do not switch to Jobs view when completed");
    result["Submit only"] = QString("Only submit simulation for consequent execution, has to be started from Jobs view explicitely");
    return result;
}

}

QStringList JobItem::m_status_list = QStringList()
        << QString("Idle")
        << QString("Running")
        << QString("Completed")
        << QString("Canceled")
        << QString("Failed");

QMap<QString, QString> JobItem::m_run_policies = initializeRunPolicies();

JobItem::JobItem(const QString &name)
    : m_name(name)
    , m_status(IDLE)
    , m_progress(0)
    , m_nthreads(0)
    , m_run_policy(SUBMIT_ONLY)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
//    initOutputDataItem();
}

JobItem::JobItem(SampleModel *sampleModel, InstrumentModel *instrumentModel, const QString &run_policy)
    : m_status(IDLE)
    , m_progress(0)
    , m_nthreads(0)
    , m_run_policy(SUBMIT_ONLY)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
{
//    initOutputDataItem();
    setRunPolicy(run_policy);
}


JobItem::~JobItem()
{
    clear();
}


void JobItem::clear()
{
    qDeleteAll(m_data_items);
    m_data_items.clear();
    delete m_sampleModel;
    delete m_instrumentModel;
}


void JobItem::initOutputDataItem()
{
    qDeleteAll(m_data_items);
    m_data_items.clear();
    OutputDataItem *dataItem = new OutputDataItem();
    m_data_items.append(dataItem);
    connect(dataItem, SIGNAL(modified()), this, SLOT(onDataItemModified()));
}


void JobItem::setResults(const Simulation *simulation)
{
    if(!simulation)
        throw GUIHelpers::Error("JobItem::setResults() -> Error. Null simulation.");

//    qDeleteAll(m_data_items);
//    m_data_items.clear();
    if(m_data_items.isEmpty()) {
        OutputDataItem *dataItem = new OutputDataItem();
        m_data_items.append(dataItem);
        connect(dataItem, SIGNAL(modified()), this, SLOT(onDataItemModified()));

    }

    OutputDataItem *outputDataItem = m_data_items.front();

    // propagatind angle units to OutputDataItem
    if(m_instrumentModel) {
        InstrumentItem *instrumentItem = dynamic_cast<InstrumentItem *>(m_instrumentModel->getInstrumentMap().begin().value());
        qDebug() << instrumentItem->modelType();
        Q_ASSERT(instrumentItem);
        DetectorItem *detectorItem = instrumentItem->getDetectorItem();
        Q_ASSERT(detectorItem);
        ParameterizedItem *subDetector = detectorItem->getSubItems()[DetectorItem::P_DETECTOR];
        Q_ASSERT(subDetector);

        if (subDetector->modelType() == Constants::PhiAlphaDetectorType) {
            AngleProperty angle_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_AXES_UNITS).value<AngleProperty>();
            if(angle_property.inDegrees())
                outputDataItem->setAxesUnits("Degrees");
        }

    }

    qDebug() << "JobItem::setResults()" << outputDataItem;

    outputDataItem->setName(QString("data_%1_%2.int").arg(m_name, QString::number(0)));
    outputDataItem->setOutputData(simulation->getIntensityData());
}


void JobItem::setName(QString name)
{
    m_name = name;
    // setting names for OutputDataItem's
    int n_data(0);
    foreach(OutputDataItem *dataItem, m_data_items) {
        QString dataFileName = QString("data_%1_%2.int").arg(m_name, QString::number(n_data));
        dataItem->setName(dataFileName);
        ++n_data;
    }

    emit modified(this);
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


// FIXME Make it nicer
void JobItem::setRunPolicy(const QString &run_policy)
{
    if(run_policy == QString("Immediately")) {
        m_run_policy = RUN_IMMEDIATELY;
    } else if(run_policy == QString("In background")) {
        m_run_policy = RUN_IN_BACKGROUND;
    } else {
        m_run_policy = SUBMIT_ONLY;
    }
//    if(run_policy )
//    int index = m_run_policies.indexOf(run_policy);
//    if(index != -1) {
//        m_run_policy = (RunPolicy)index;
//    } else {
//        m_run_policy = SubmitOnly;
//    }
}

SampleModel *JobItem::getSampleModel()
{
    return m_sampleModel;
}


void JobItem::setSampleModel(SampleModel *sampleModel)
{
    delete m_sampleModel;
    m_sampleModel = sampleModel;
}


InstrumentModel *JobItem::getInstrumentModel()
{
    return m_instrumentModel;
}


void JobItem::setInstrumentModel(InstrumentModel *instrumentModel)
{
    delete m_instrumentModel;
    m_instrumentModel = instrumentModel;
}


void JobItem::writeTo(QXmlStreamWriter *writer)
{
    Q_ASSERT(writer);
    writer->writeStartElement(JobQueueXML::JobTag);
    writer->writeAttribute(JobQueueXML::JobNameAttribute, getName());
    writer->writeAttribute(JobQueueXML::JobStatusAttribute, QString::number((int)getStatus()));
    writer->writeAttribute(JobQueueXML::JobBeginTimeAttribute, getBeginTime());
    writer->writeAttribute(JobQueueXML::JobEndTimeAttribute, getEndTime());
    writer->writeAttribute(JobQueueXML::JobProgressAttribute, QString::number((int)getProgress()));
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

    EJobStatus status = (EJobStatus) (reader->attributes()
            .value(JobQueueXML::JobStatusAttribute).toInt());
    setStatus(status);

    setProgress(reader->attributes()
                .value(JobQueueXML::JobProgressAttribute).toInt());

    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {

            if (reader->name() == JobQueueXML::OutputDataTag) {
                qDebug() << "JobItem::readFrom() -> output data";
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


