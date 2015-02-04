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

const QString NJobItem::P_IDENTIFIER = "Identifier";
const QString NJobItem::P_BEGIN_TYPE = "Begin Time";
const QString NJobItem::P_END_TYPE = "End Time";
const QString NJobItem::P_COMMENTS = "Comments";
const QString NJobItem::P_STATUS = "Status";
const QString NJobItem::P_PROGRESS = "Progress";
const QString NJobItem::P_NTHREADS = "Number of Threads";
const QString NJobItem::P_RUN_POLICY = "Run Policy";

namespace {
const QString STATUS_IDLE = "Idle";
const QString STATUS_RUNNING = "Running";
const QString STATUS_COMPLETED = "Completed";
const QString STATUS_CANCELED = "Canceled";
const QString STATUS_FAILED = "Failed";
}

NJobItem::NJobItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::JobItemType, parent)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    setItemName(Constants::JobItemType);
    registerProperty(P_IDENTIFIER, QString());
    registerProperty(P_BEGIN_TYPE, QString());
    registerProperty(P_BEGIN_TYPE, QString());
    registerProperty(P_END_TYPE, QString());
    registerProperty(P_COMMENTS, QString());

    ComboProperty status;
    status << STATUS_IDLE << STATUS_RUNNING << STATUS_COMPLETED << STATUS_CANCELED << STATUS_FAILED;
    registerProperty(P_STATUS, status.getVariant());

    registerProperty(P_PROGRESS, 0);
    registerProperty(P_NTHREADS, -1);

    ComboProperty policy;
    policy << QString("Immediately") << QString("In background") << QString("Submit only");
    registerProperty(P_RUN_POLICY, policy.getVariant());

    addToValidChildren(Constants::IntensityDataType);

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
}


InstrumentModel *NJobItem::getInstrumentModel()
{
    return m_instrumentModel;
}


void NJobItem::setInstrumentModel(InstrumentModel *instrumentModel)
{
    delete m_instrumentModel;
    m_instrumentModel = instrumentModel;
}

bool NJobItem::isIdle() const
{
    return getRegisteredProperty(P_STATUS).toString() == STATUS_IDLE;
}

bool NJobItem::isRunning() const
{
    return getRegisteredProperty(P_STATUS).toString() == STATUS_RUNNING;
}

bool NJobItem::isCompleted() const
{
    return getRegisteredProperty(P_STATUS).toString() == STATUS_COMPLETED;
}

bool NJobItem::isCanceled() const
{
    return getRegisteredProperty(P_STATUS).toString() == STATUS_CANCELED;
}

bool NJobItem::isFailed() const
{
    return getRegisteredProperty(P_STATUS).toString() == STATUS_FAILED;
}

QString NJobItem::getIdentifier() const
{
    return getRegisteredProperty(P_IDENTIFIER).toString();
}


