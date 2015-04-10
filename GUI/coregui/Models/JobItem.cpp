// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobItem.cpp
//! @brief     Implements class NJobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobItem.h"
#include "ComboProperty.h"
#include "IntensityDataItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"


namespace
{
const QString RUN_IMMEDIATELY = "Immediately";
const QString RUN_IN_BACKGROUND = "In background";
const QString RUN_SUBMIT_ONLY = "Submit only";

QMap<QString, QString> initializeRunPolicies()
{
    QMap<QString, QString> result;
    result[RUN_IMMEDIATELY] = QString("Start simulation immediately, switch to Jobs view automatically when completed");
    result[RUN_IN_BACKGROUND] = QString("Start simulation immediately, do not switch to Jobs view when completed");
    result[RUN_SUBMIT_ONLY] = QString("Only submit simulation for consequent execution, has to be started from Jobs view explicitely");
    return result;
}

}

QMap<QString, QString> JobItem::m_run_policies = initializeRunPolicies();


const QString JobItem::P_IDENTIFIER = "Identifier";
const QString JobItem::P_SAMPLE_NAME = "Sample";
const QString JobItem::P_INSTRUMENT_NAME = "Instrument";
const QString JobItem::P_STATUS = "Status";
const QString JobItem::P_BEGIN_TIME = "Begin Time";
const QString JobItem::P_END_TIME = "End Time";
const QString JobItem::P_COMMENTS = "Comments";
const QString JobItem::P_PROGRESS = "Progress";
const QString JobItem::P_NTHREADS = "Number of Threads";
const QString JobItem::P_RUN_POLICY = "Run Policy";


JobItem::JobItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::JobItemType, parent)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    setItemName(Constants::JobItemType);
    registerProperty(P_IDENTIFIER, QString(), PropertyAttribute(PropertyAttribute::HIDDEN));
    registerProperty(P_SAMPLE_NAME, QString(), PropertyAttribute(PropertyAttribute::READONLY));
    registerProperty(P_INSTRUMENT_NAME, QString(), PropertyAttribute(PropertyAttribute::READONLY));

    ComboProperty status;
    status << Constants::STATUS_IDLE << Constants::STATUS_RUNNING << Constants::STATUS_COMPLETED
           << Constants::STATUS_CANCELED << Constants::STATUS_FAILED;
    registerProperty(P_STATUS, status.getVariant(), PropertyAttribute(PropertyAttribute::READONLY));

    registerProperty(P_BEGIN_TIME, QString(), PropertyAttribute(PropertyAttribute::READONLY));
    registerProperty(P_END_TIME, QString(), PropertyAttribute(PropertyAttribute::READONLY));
    registerProperty(P_COMMENTS, QString(), PropertyAttribute(PropertyAttribute::HIDDEN));

    registerProperty(P_PROGRESS, 0, PropertyAttribute(PropertyAttribute::HIDDEN));
    registerProperty(P_NTHREADS, -1, PropertyAttribute(PropertyAttribute::HIDDEN));

    ComboProperty policy;
    policy << RUN_IMMEDIATELY <<RUN_IN_BACKGROUND << RUN_SUBMIT_ONLY;
    registerProperty(P_RUN_POLICY, policy.getVariant(), PropertyAttribute(PropertyAttribute::HIDDEN));

    addToValidChildren(Constants::IntensityDataType);

    setPropertyAppearance(ParameterizedItem::P_NAME, PropertyAttribute::VISIBLE);


}

JobItem::~JobItem()
{
    delete m_sampleModel;
    delete m_instrumentModel;
}

QString JobItem::getIdentifier() const
{
    return getRegisteredProperty(P_IDENTIFIER).toString();
}

void JobItem::setIdentifier(const QString &identifier)
{
    setRegisteredProperty(JobItem::P_IDENTIFIER, identifier);
}

IntensityDataItem *JobItem::getIntensityDataItem()
{
    foreach(ParameterizedItem *item, childItems()) {
        IntensityDataItem *data = dynamic_cast<IntensityDataItem *>(item);
        if(data) return data;
    }
    return 0;
}

SampleModel *JobItem::getSampleModel()
{
    return m_sampleModel;
}

void JobItem::setSampleModel(SampleModel *sampleModel)
{
    delete m_sampleModel;
    m_sampleModel = sampleModel;
    if(m_sampleModel) {
        setRegisteredProperty(P_SAMPLE_NAME, m_sampleModel->getSampleMap().firstKey());
    }
}

InstrumentModel *JobItem::getInstrumentModel()
{
    return m_instrumentModel;
}

void JobItem::setInstrumentModel(InstrumentModel *instrumentModel)
{
    delete m_instrumentModel;
    m_instrumentModel = instrumentModel;
    if(m_instrumentModel) {
        setRegisteredProperty(P_INSTRUMENT_NAME, m_instrumentModel->getInstrumentMap().firstKey());
    }
}

QString JobItem::getStatus() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue();
}

void JobItem::setStatus(const QString &status)
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    combo_property.setValue(status);
    setRegisteredProperty(P_STATUS, combo_property.getVariant());
    if(status == Constants::STATUS_FAILED) {
        if(IntensityDataItem *intensityItem = getIntensityDataItem()) {
            if(intensityItem->getOutputData())
                intensityItem->getOutputData()->setAllTo(0.0);
                emit intensityItem->intensityModified();
        }
    }
}

bool JobItem::isIdle() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_IDLE;
}

bool JobItem::isRunning() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_RUNNING;
}

bool JobItem::isCompleted() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_COMPLETED;
}

bool JobItem::isCanceled() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_CANCELED;
}

bool JobItem::isFailed() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_FAILED;
}

void JobItem::setBeginTime(const QString &begin_time)
{
    setRegisteredProperty(P_BEGIN_TIME, begin_time);
}

void JobItem::setEndTime(const QString &end_time)
{
    setRegisteredProperty(P_END_TIME, end_time);
}

QString JobItem::getComments() const
{
    return getRegisteredProperty(P_COMMENTS).toString();
}

void JobItem::setComments(const QString &comments)
{
    setRegisteredProperty(P_COMMENTS, comments);
}

int JobItem::getProgress() const
{
    return getRegisteredProperty(P_PROGRESS).toInt();
}

void JobItem::setProgress(int progress)
{
    setRegisteredProperty(P_PROGRESS, progress);
}

int JobItem::getNumberOfThreads() const
{
    return getRegisteredProperty(P_NTHREADS).toInt();
}

void JobItem::setNumberOfThreads(int number_of_threads)
{
    setRegisteredProperty(P_NTHREADS, number_of_threads);
}

bool JobItem::runImmediately() const
{
    ComboProperty combo_property = getRegisteredProperty(P_RUN_POLICY).value<ComboProperty>();
    return combo_property.getValue() == RUN_IMMEDIATELY;
}

bool JobItem::runInBackground() const
{
    ComboProperty combo_property = getRegisteredProperty(P_RUN_POLICY).value<ComboProperty>();
    return combo_property.getValue() == RUN_IN_BACKGROUND;
}
