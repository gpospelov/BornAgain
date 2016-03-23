// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobItem.cpp
//! @brief     Implements class JobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobItem.h"
#include "ComboProperty.h"
#include "IntensityDataItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include "JobResultsPresenter.h"
#include <QDebug>


namespace
{

QMap<QString, QString> initializeRunPolicies()
{
    QMap<QString, QString> result;
    result[Constants::JOB_RUN_IMMEDIATELY] =
        QString("Start simulation immediately, switch to Jobs view automatically when completed");
    result[Constants::JOB_RUN_IN_BACKGROUND] =
        QString("Start simulation immediately, do not switch to Jobs view when completed");
    result[Constants::JOB_RUN_SUBMIT_ONLY] =
        QString("Only submit simulation for consequent execution,"
                " has to be started from Jobs view explicitely");
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


JobItem::JobItem()
    : SessionItem(Constants::JobItemType)
{
//    registerProperty(OBSOLETE_P_NAME, Constants::JobItemType);
    setItemName(Constants::JobItemType);
    addProperty(P_IDENTIFIER, QString())->setVisible(false);
    addProperty(P_SAMPLE_NAME, QString())->setEditable(false);
    addProperty(P_INSTRUMENT_NAME, QString())->setEditable(false);

    ComboProperty status;
    status << Constants::STATUS_IDLE << Constants::STATUS_RUNNING << Constants::STATUS_COMPLETED
           << Constants::STATUS_CANCELED << Constants::STATUS_FAILED;
    addProperty(P_STATUS, status.getVariant())->setEditable(false);

    addProperty(P_BEGIN_TIME, QString())->setEditable(false);
    addProperty(P_END_TIME, QString())->setEditable(false);
    addProperty(P_COMMENTS, QString())->setVisible(false);

    addProperty(P_PROGRESS, 0)->setVisible(false);
    addProperty(P_NTHREADS, -1)->setVisible(false);

    ComboProperty policy;
    policy << Constants::JOB_RUN_IMMEDIATELY
           << Constants::JOB_RUN_IN_BACKGROUND
           << Constants::JOB_RUN_SUBMIT_ONLY;
    addProperty(P_RUN_POLICY, policy.getVariant())->setVisible(false);

    const QString T_DATA = "Data Tag";
    registerTag("Data Tag", 0, -1, QStringList() << Constants::IntensityDataType
                << Constants::MultiLayerType << Constants::InstrumentType);
    setDefaultTag(T_DATA);
    mapper()->setOnChildPropertyChange(
                [this](SessionItem* item, const QString &name)
    {
        if (item->modelType() == Constants::IntensityDataType
            && name == IntensityDataItem::P_AXES_UNITS) {
            auto intensityItem = dynamic_cast<IntensityDataItem *>(item);
            JobResultsPresenter::updateDataAxes(intensityItem, getInstrumentItem());
            qDebug() << "QQQQ" << item->modelType() << name;

        }
    });
}

JobItem::~JobItem()
{
}

QString JobItem::getIdentifier() const
{
    return getItemValue(P_IDENTIFIER).toString();
}

void JobItem::setIdentifier(const QString &identifier)
{
    setItemValue(JobItem::P_IDENTIFIER, identifier);
}

IntensityDataItem *JobItem::getIntensityDataItem()
{
    foreach(SessionItem *item, childItems()) {
        IntensityDataItem *data = dynamic_cast<IntensityDataItem *>(item);
        if(data) return data;
    }
    return 0;
}

QString JobItem::getStatus() const
{
    ComboProperty combo_property = getItemValue(P_STATUS).value<ComboProperty>();
    return combo_property.getValue();
}

void JobItem::setStatus(const QString &status)
{
    ComboProperty combo_property = getItemValue(P_STATUS).value<ComboProperty>();
    combo_property.setValue(status);
    setItemValue(P_STATUS, combo_property.getVariant());
    if(status == Constants::STATUS_FAILED) {
        if(IntensityDataItem *intensityItem = getIntensityDataItem()) {
            if(intensityItem->getOutputData())
                intensityItem->getOutputData()->setAllTo(0.0);
                emit intensityItem->emitDataChanged();
        }
    }
}

bool JobItem::isIdle() const
{
    ComboProperty combo_property = getItemValue(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_IDLE;
}

bool JobItem::isRunning() const
{
    ComboProperty combo_property = getItemValue(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_RUNNING;
}

bool JobItem::isCompleted() const
{
    ComboProperty combo_property = getItemValue(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_COMPLETED;
}

bool JobItem::isCanceled() const
{
    ComboProperty combo_property = getItemValue(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_CANCELED;
}

bool JobItem::isFailed() const
{
    ComboProperty combo_property = getItemValue(P_STATUS).value<ComboProperty>();
    return combo_property.getValue() == Constants::STATUS_FAILED;
}

void JobItem::setBeginTime(const QString &begin_time)
{
    setItemValue(P_BEGIN_TIME, begin_time);
}

void JobItem::setEndTime(const QString &end_time)
{
    setItemValue(P_END_TIME, end_time);
}

QString JobItem::getComments() const
{
    return getItemValue(P_COMMENTS).toString();
}

void JobItem::setComments(const QString &comments)
{
    setItemValue(P_COMMENTS, comments);
}

int JobItem::getProgress() const
{
    return getItemValue(P_PROGRESS).toInt();
}

void JobItem::setProgress(int progress)
{
    setItemValue(P_PROGRESS, progress);
}

int JobItem::getNumberOfThreads() const
{
    return getItemValue(P_NTHREADS).toInt();
}

void JobItem::setNumberOfThreads(int number_of_threads)
{
    setItemValue(P_NTHREADS, number_of_threads);
}

void JobItem::setRunPolicy(const QString &run_policy)
{
    ComboProperty combo_property = getItemValue(JobItem::P_RUN_POLICY).value<ComboProperty>();
    combo_property.setValue(run_policy);
    setItemValue(JobItem::P_RUN_POLICY, combo_property.getVariant());
}

bool JobItem::runImmediately() const
{
    ComboProperty combo_property = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    return combo_property.getValue() == Constants::JOB_RUN_IMMEDIATELY;
}

bool JobItem::runInBackground() const
{
    ComboProperty combo_property = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    return combo_property.getValue() == Constants::JOB_RUN_IN_BACKGROUND;
}

//! Returns MultiLayerItem of this JobItem, if from_backup=true, then backup'ed version of
//! multilayer will be used
MultiLayerItem *JobItem::getMultiLayerItem(bool from_backup)
{
    foreach(SessionItem *item, childItems()) {
        if(MultiLayerItem *multilayer = dynamic_cast<MultiLayerItem *>(item)) {
            if(from_backup && multilayer->itemName().endsWith(Constants::JOB_BACKUP)) {
                return multilayer;
            }
            if(!from_backup && !multilayer->itemName().endsWith(Constants::JOB_BACKUP)) {
                return multilayer;
            }
        }
    }
    return 0;
}

//! Returns InstrumentItem of this JobItem, if from_backup=true, then backup'ed version of
//! the instrument will be used
InstrumentItem *JobItem::getInstrumentItem(bool from_backup)
{
    foreach(SessionItem *item, childItems()) {
        if(InstrumentItem *instrument = dynamic_cast<InstrumentItem *>(item)) {
            if(from_backup && instrument->itemName().endsWith(Constants::JOB_BACKUP)) {
                return instrument;
            }
            if(!from_backup && !instrument->itemName().endsWith(Constants::JOB_BACKUP)) {
                return instrument;
            }
        }
    }
    return 0;
}

void JobItem::setResults(const GISASSimulation *simulation)
{
    IntensityDataItem *intensityItem = getIntensityDataItem();
    Q_ASSERT(intensityItem);

    JobResultsPresenter::setResults(intensityItem, simulation);
}

