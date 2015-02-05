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

#include "NJobItem.h"
#include "ComboProperty.h"
#include "NIntensityDataItem.h"
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

QMap<QString, QString> NJobItem::m_run_policies = initializeRunPolicies();


const QString NJobItem::P_IDENTIFIER = "Identifier";
const QString NJobItem::P_SAMPLE_NAME = "Sample";
const QString NJobItem::P_INSTRUMENT_NAME = "Instrument";
const QString NJobItem::P_STATUS = "Status";
const QString NJobItem::P_BEGIN_TIME = "Begin Time";
const QString NJobItem::P_END_TIME = "End Time";
const QString NJobItem::P_COMMENTS = "Comments";
const QString NJobItem::P_PROGRESS = "Progress";
const QString NJobItem::P_NTHREADS = "Number of Threads";
const QString NJobItem::P_RUN_POLICY = "Run Policy";


NJobItem::NJobItem(ParameterizedItem *parent)
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

QString NJobItem::getIdentifier() const
{
    return getRegisteredProperty(P_IDENTIFIER).toString();
}

void NJobItem::setIdentifier(const QString &identifier)
{
    setRegisteredProperty(NJobItem::P_IDENTIFIER, identifier);
}

NIntensityDataItem *NJobItem::getIntensityDataItem()
{
    foreach(ParameterizedItem *item, childItems()) {
        NIntensityDataItem *data = dynamic_cast<NIntensityDataItem *>(item);
        if(data) return data;
    }
    return 0;
}

SampleModel *NJobItem::getSampleModel()
{
    return m_sampleModel;
}

void NJobItem::setSampleModel(SampleModel *sampleModel)
{
    delete m_sampleModel;
    m_sampleModel = sampleModel;
    if(m_sampleModel) {
        setRegisteredProperty(P_SAMPLE_NAME, m_sampleModel->getSampleMap().firstKey());
    }
}

InstrumentModel *NJobItem::getInstrumentModel()
{
    return m_instrumentModel;
}

void NJobItem::setInstrumentModel(InstrumentModel *instrumentModel)
{
    delete m_instrumentModel;
    m_instrumentModel = instrumentModel;
    if(m_instrumentModel) {
        setRegisteredProperty(P_INSTRUMENT_NAME, m_instrumentModel->getInstrumentMap().firstKey());
    }
}

QString NJobItem::getStatus() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue();
}

void NJobItem::setStatus(const QString &status)
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    combo_property.setValue(status);
    setRegisteredProperty(P_STATUS, combo_property.getVariant());
}

bool NJobItem::isIdle() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_IDLE;
}

bool NJobItem::isRunning() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_RUNNING;
}

bool NJobItem::isCompleted() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_COMPLETED;
}

bool NJobItem::isCanceled() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_CANCELED;
}

bool NJobItem::isFailed() const
{
    ComboProperty combo_property = getRegisteredProperty(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_FAILED;
}

void NJobItem::setBeginTime(const QString &begin_time)
{
    setRegisteredProperty(P_BEGIN_TIME, begin_time);
}

void NJobItem::setEndTime(const QString &end_time)
{
    setRegisteredProperty(P_END_TIME, end_time);
}

QString NJobItem::getComments() const
{
    return getRegisteredProperty(P_COMMENTS).toString();
}

void NJobItem::setComments(const QString &comments)
{
    setRegisteredProperty(P_COMMENTS, comments);
}

int NJobItem::getProgress() const
{
    return getRegisteredProperty(P_PROGRESS).toInt();
}

void NJobItem::setProgress(int progress)
{
    setRegisteredProperty(P_PROGRESS, progress);
}

int NJobItem::getNumberOfThreads() const
{
    return getRegisteredProperty(P_NTHREADS).toInt();
}

void NJobItem::setNumberOfThreads(int number_of_threads)
{
    setRegisteredProperty(P_NTHREADS, number_of_threads);
}

bool NJobItem::runImmediately() const
{
    ComboProperty combo_property = getRegisteredProperty(P_RUN_POLICY).value<ComboProperty>();
    return combo_property.getValue() == RUN_IMMEDIATELY;
}

bool NJobItem::runInBackground() const
{
    ComboProperty combo_property = getRegisteredProperty(P_RUN_POLICY).value<ComboProperty>();
    return combo_property.getValue() == RUN_IN_BACKGROUND;
}
