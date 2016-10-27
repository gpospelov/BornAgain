// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItem.cpp
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
#include "FitSuiteItem.h"
#include "GUIHelpers.h"
#include "InstrumentItem.h"
#include "IntensityDataItem.h"
#include "JobItemHelper.h"
#include "MultiLayerItem.h"
#include "ParameterTreeItems.h"
#include "RealDataItem.h"
#include "SimulationOptionsItem.h"
#include "IntensityDataItem.h"
#include "JobItemFunctions.h"
#include <QDebug>

namespace {
    QVariant createStatusVariant() {
        ComboProperty status;
        status << Constants::STATUS_IDLE << Constants::STATUS_RUNNING
               << Constants::STATUS_FITTING << Constants::STATUS_COMPLETED
               << Constants::STATUS_CANCELED << Constants::STATUS_FAILED;
        return status.getVariant();
    }
}

const QString JobItem::P_IDENTIFIER = "Identifier";
const QString JobItem::P_SAMPLE_NAME = "Sample";
const QString JobItem::P_INSTRUMENT_NAME = "Instrument";
const QString JobItem::P_WITH_FITTING = "With Fitting";
const QString JobItem::P_STATUS = "Status";
const QString JobItem::P_BEGIN_TIME = "Begin Time";
const QString JobItem::P_END_TIME = "End Time";
const QString JobItem::P_DURATION = "Duration";
const QString JobItem::P_COMMENTS = "Comments";
const QString JobItem::P_PROGRESS = "Progress";
const QString JobItem::T_SAMPLE = "Sample Tag";
const QString JobItem::T_INSTRUMENT = "Instrument Tag";
const QString JobItem::T_OUTPUT = "Output Tag";
const QString JobItem::T_REALDATA = "Real Data Tag";
const QString JobItem::T_PARAMETER_TREE = "Parameter Tree";
const QString JobItem::T_SIMULATION_OPTIONS = "Simulation Options";
const QString JobItem::T_FIT_SUITE = "Fit Suite";

JobItem::JobItem()
    : SessionItem(Constants::JobItemType)
{
    setItemName(Constants::JobItemType);
    addProperty(P_IDENTIFIER, QString())->setVisible(false);
    addProperty(P_SAMPLE_NAME, QString())->setEditable(false);
    addProperty(P_INSTRUMENT_NAME, QString())->setEditable(false);
    addProperty(P_WITH_FITTING, false)->setVisible(false);

//    ComboProperty status;
//    status << Constants::STATUS_IDLE << Constants::STATUS_RUNNING << Constants::STATUS_FITTING << Constants::STATUS_COMPLETED
//           << Constants::STATUS_CANCELED << Constants::STATUS_FAILED;
    addProperty(P_STATUS, createStatusVariant())->setEditable(false);

    addProperty(P_BEGIN_TIME, QString())->setEditable(false);
    addProperty(P_END_TIME, QString())->setEditable(false);

    SessionItem *durationItem = addProperty(P_DURATION, QString());
    durationItem->setEditable(false);
    durationItem->setToolTip(QStringLiteral("Duration of DWBA simulation in sec.msec format"));

    addProperty(P_COMMENTS, QString())->setVisible(false);
    addProperty(P_PROGRESS, 0)->setVisible(false);

    registerTag(T_SAMPLE, 1, 1, QStringList() << Constants::MultiLayerType);
    registerTag(T_INSTRUMENT, 1, 1, QStringList() << Constants::InstrumentType);
    registerTag(T_OUTPUT, 1, 1, QStringList() << Constants::IntensityDataType);
    registerTag(T_REALDATA, 1, 1, QStringList() << Constants::RealDataType);
//    registerTag(T_PARAMETER_TREE, 0, -1, QStringList() << Constants::ParameterLabelType
//                << Constants::ParameterType);
    registerTag(T_PARAMETER_TREE, 0, -1, QStringList() << Constants::ParameterContainerType);

    registerTag(T_SIMULATION_OPTIONS, 1, 1, QStringList() << Constants::SimulationOptionsType);

    registerTag(T_FIT_SUITE, 1, 1, QStringList() << Constants::FitSuiteType);

    mapper()->setOnChildPropertyChange(
                [this](SessionItem* item, const QString &name)
    {
        if (item->parent() == this && item->modelType() == Constants::IntensityDataType
            && name == IntensityDataItem::P_AXES_UNITS) {
            auto intensityItem = dynamic_cast<IntensityDataItem *>(item);
            JobItemHelper::updateDataAxes(intensityItem, instrumentItem());
        }
    });

    mapper()->setOnPropertyChange(
        [this](const QString &name){
        if(name == P_NAME)
            updateIntensityDataFileName();
        }
    );

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

IntensityDataItem *JobItem::intensityDataItem()
{
    return dynamic_cast<IntensityDataItem*>(getItem(T_OUTPUT));
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
        if(IntensityDataItem *intensityItem = intensityDataItem()) {
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

bool JobItem::isValidForFitting()
{
    if(isTag(T_REALDATA) && getItem(T_REALDATA)) {
        return true;
    } else {
        return false;
    }
}

void JobItem::setBeginTime(const QString &begin_time)
{
    setItemValue(P_BEGIN_TIME, begin_time);
}

void JobItem::setEndTime(const QString &end_time)
{
    setItemValue(P_END_TIME, end_time);
}

// Sets duration (msec -> "sec.msec")
void JobItem::setDuration(int duration)
{
    QString str;
    if(duration != 0)
        str.sprintf("%7.3f", duration/1000.);
    setItemValue(P_DURATION, str.simplified());
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
    return getSimulationOptionsItem()->getNumberOfThreads();
}

void JobItem::setRunPolicy(const QString &run_policy)
{
    getSimulationOptionsItem()->setRunPolicy(run_policy);
}

bool JobItem::runImmediately() const
{
    return getSimulationOptionsItem()->runImmediately();
}

bool JobItem::runInBackground() const
{
    return getSimulationOptionsItem()->runInBackground();
}

//! Returns MultiLayerItem of this JobItem, if from_backup=true, then backup'ed version of
//! multilayer will be used
MultiLayerItem *JobItem::multiLayerItem()
{
    return dynamic_cast<MultiLayerItem*>(getItem(T_SAMPLE));
}

//! Returns InstrumentItem of this JobItem, if from_backup=true, then backup'ed version of
//! the instrument will be used
InstrumentItem *JobItem::instrumentItem()
{
    return dynamic_cast<InstrumentItem*>(getItem(T_INSTRUMENT));
}

void JobItem::setResults(const GISASSimulation *simulation)
{
    IntensityDataItem *intensityItem = intensityDataItem();
    Q_ASSERT(intensityItem);

    JobItemHelper::setResults(intensityItem, simulation);
    updateIntensityDataFileName();
}

FitSuiteItem *JobItem::fitSuiteItem()
{
    return dynamic_cast<FitSuiteItem *>(getItem(JobItem::T_FIT_SUITE));
}

ParameterContainerItem *JobItem::parameterContainerItem()
{
    return dynamic_cast<ParameterContainerItem *>(getItem(JobItem::T_PARAMETER_TREE));
}

FitParameterContainerItem *JobItem::fitParameterContainerItem()
{
    if(FitSuiteItem *item = fitSuiteItem())
        return item->fitParameterContainerItem();

    return nullptr;
}

RealDataItem *JobItem::realDataItem()
{
    return dynamic_cast<RealDataItem*>(getItem(JobItem::T_REALDATA));
}

//! Updates the name of file to store intensity data.

void JobItem::updateIntensityDataFileName()
{
    if(IntensityDataItem *item = intensityDataItem())
        item->setItemValue(IntensityDataItem::P_FILE_NAME,
                           JobItemFunctions::jobResultsFileName(*this));

    if(RealDataItem *realItem = realDataItem())
        if(IntensityDataItem *item = realItem->intensityDataItem())
            item->setItemValue(IntensityDataItem::P_FILE_NAME,
                               JobItemFunctions::jobReferenceFileName(*this));

}

SimulationOptionsItem *JobItem::getSimulationOptionsItem()
{
    return const_cast<SimulationOptionsItem *>(static_cast<const JobItem*>(this)->getSimulationOptionsItem());
}

const SimulationOptionsItem *JobItem::getSimulationOptionsItem() const
{
    const SimulationOptionsItem *result = dynamic_cast<const SimulationOptionsItem *>(getItem(T_SIMULATION_OPTIONS));
    if(!result) {
        throw GUIHelpers::Error("JobItem::getSimulationOptions() -> Error. "
                                "Can't get SimulationOptionsItem");
    }
    return result;
}

