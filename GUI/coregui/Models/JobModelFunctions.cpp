// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobModelFunctions.cpp
//! @brief     Implements auxiliary functions in JobModelFunctions namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "JobModelFunctions.h"
#include "JobModel.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "FitSuiteItem.h"
#include "InstrumentItems.h"
#include "GUIHelpers.h"
#include "MaskUnitsConverter.h"
#include "DetectorItems.h"
#include "MaskItems.h"
#include "DetectorFunctions.h"
#include "DomainObjectBuilder.h"
#include "Instrument.h"
#include "JobItemUtils.h"
#include "IDetector2D.h"
#include "JobItemFunctions.h"

namespace JobModelFunctions {
void copyRealDataItem(JobItem *jobItem, const RealDataItem *realDataItem);
void processInstrumentLink(JobItem *jobItem);
void copyMasksToInstrument(JobItem *jobItem);
void cropRealData(JobItem *jobItem);
void createFitContainers(JobItem *jobItem);
}


//! Setup items intended for storing results of the job.

void JobModelFunctions::setupJobItemOutput(JobItem* jobItem)
{
    auto model = jobItem->model();

    auto instrumentType = jobItem->instrumentItem()->modelType();
    if (instrumentType == Constants::SpecularInstrumentType) {
        model->insertNewItem(Constants::SpecularDataType,
                         model->indexOfItem(jobItem), -1, JobItem::T_OUTPUT);

    } else if(instrumentType == Constants::GISASInstrumentType ||
              instrumentType == Constants::OffSpecInstrumentType) {

        model->insertNewItem(Constants::IntensityDataType,
                         model->indexOfItem(jobItem), -1, JobItem::T_OUTPUT);
    } else {
        throw GUIHelpers::Error("JobModelFunctions::setupJobItemOutput() -> Error. "
                                "Unsupported instrument type");
    }

}

//! Setups JobItem for fit.

void JobModelFunctions::setupJobItemForFit(JobItem *jobItem, const RealDataItem *realDataItem)
{
    if(!jobItem->instrumentItem())
        throw GUIHelpers::Error("JobModelFunctions::processInstrumentLink() -> Error. "
                                "No instrument.");

    JobModelFunctions::copyRealDataItem(jobItem, realDataItem);
    JobModelFunctions::processInstrumentLink(jobItem);
    JobModelFunctions::copyMasksToInstrument(jobItem);

    // TODO: remove if when other simulation types are ready for roi & masks
    if (jobItem->instrumentItem()->modelType() == Constants::GISASInstrumentType)
        JobModelFunctions::cropRealData(jobItem);

    JobModelFunctions::createFitContainers(jobItem);
}


//! Copy RealDataItem to jobItem intended for fitting.

void JobModelFunctions::copyRealDataItem(JobItem *jobItem, const RealDataItem *realDataItem)
{
    if(!realDataItem)
        return;

    SessionModel *model = jobItem->model();

    RealDataItem *realDataItemCopy = dynamic_cast<RealDataItem *>(
        model->copyItem(realDataItem, jobItem, JobItem::T_REALDATA));
    Q_ASSERT(realDataItemCopy);

    realDataItemCopy->dataItem()->setOutputData(
                realDataItem->dataItem()->getOutputData()->clone());

    // adapting the name to job name
    realDataItemCopy->dataItem()->setItemValue(DataItem::P_FILE_NAME,
        JobItemFunctions::jobReferenceFileName(*jobItem));
}

//! Links RealDataItem to the JobItem's instrument.
// (re-)Linking is necessary because of following reason
// 1) Copying of RealDataItem from RealDataModel on board of JobItem requires relink to the copied
//    insturment
// 2) During relink all masks (if exists) will be converted to the default units of current detector

void JobModelFunctions::processInstrumentLink(JobItem *jobItem)
{
    RealDataItem *realData = jobItem->realDataItem();
    if(!realData)
        throw GUIHelpers::Error("JobModelFunctions::processInstrumentLink() -> Error. No data.");

    realData->linkToInstrument(jobItem->instrumentItem());
}

//! Copies masks and ROI from RealDataItem on board of instrument.

void JobModelFunctions::copyMasksToInstrument(JobItem *jobItem)
{
    auto mask_container = jobItem->realDataItem()->maskContainerItem();
    jobItem->instrumentItem()->importMasks(mask_container);
}

//! Crops RealDataItem to the region of interest.

void JobModelFunctions::cropRealData(JobItem *jobItem) {
    RealDataItem *realData = jobItem->realDataItem();

    // adjusting real data to the size of region of interest
    IntensityDataItem *intensityItem = realData->intensityDataItem();

    std::unique_ptr<OutputData<double>> origData(intensityItem->getOutputData()->clone());

    JobItemUtils::createDefaultDetectorMap(intensityItem, jobItem->instrumentItem());

    auto instrument = jobItem->instrumentItem()->createInstrument();
    instrument->getDetector()->iterate(
        [&](IDetector::const_iterator it) {
            auto cropped_data = intensityItem->getOutputData();
            (*cropped_data)[it.roiIndex()] = (*origData)[it.detectorIndex()];
        },
        /*visit_masked*/ false);

    intensityItem->updateDataRange();
}

//! Creates necessary fit containers for jobItem intended for fitting.

void JobModelFunctions::createFitContainers(JobItem *jobItem)
{
    SessionModel *model = jobItem->model();

    SessionItem *fitSuiteItem = jobItem->getItem(JobItem::T_FIT_SUITE);
    if(fitSuiteItem != nullptr) {
        throw GUIHelpers::Error("JobModel::createFitContainers() -> Error. Attempt to create "
                                "a second FitSuiteItem.");
    }

    fitSuiteItem = model->insertNewItem(Constants::FitSuiteType,
                                 jobItem->index(), -1, JobItem::T_FIT_SUITE);

    SessionItem *parsContainerItem = fitSuiteItem->getItem(FitSuiteItem::T_FIT_PARAMETERS);
    if(parsContainerItem != nullptr) {
        throw GUIHelpers::Error("JobModel::createFitContainers() -> Error. Attempt to create "
                                "a second FitParameterContainer.");
    }

    parsContainerItem = model->insertNewItem(Constants::FitParameterContainerType,
                                      fitSuiteItem->index(), -1, FitSuiteItem::T_FIT_PARAMETERS);

    // Minimizer settings
    SessionItem *minimizerContainerItem = fitSuiteItem->getItem(FitSuiteItem::T_MINIMIZER);
    if(minimizerContainerItem != nullptr) {
        throw GUIHelpers::Error("JobModel::createFitContainers() -> Error. Attempt to create "
                                "a second MinimizerContainer.");
    }

    minimizerContainerItem = model->insertNewItem(Constants::MinimizerContainerType,
                                      fitSuiteItem->index(), -1, FitSuiteItem::T_MINIMIZER);

}

