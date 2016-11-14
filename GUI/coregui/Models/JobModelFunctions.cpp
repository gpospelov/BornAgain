// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobModelFunctions.cpp
//! @brief     Implements auxiliary functions in JobModelFunctions namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobModelFunctions.h"
#include "JobModel.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "FitSuiteItem.h"
#include "InstrumentItem.h"
#include "GUIHelpers.h"
#include "MaskUnitsConverter.h"
#include "DetectorItems.h"
#include "MaskItems.h"
#include "DetectorFunctions.h"
#include "DomainObjectBuilder.h"
#include "Instrument.h"
#include "JobItemHelper.h"
#include "IDetector2D.h"
#include "JobItemFunctions.h"
#include <QDebug>

namespace JobModelFunctions {
void copyRealDataItem(JobItem *jobItem, const RealDataItem *realDataItem);
void processInstrumentLink(JobItem *jobItem);
void copyMasksToInstrument(JobItem *jobItem);
void cropRealData(JobItem *jobItem);
void createFitContainers(JobItem *jobItem);
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
        model->copyParameterizedItem(realDataItem, jobItem, JobItem::T_REALDATA));
    Q_ASSERT(realDataItemCopy);

    realDataItemCopy->intensityDataItem()->setOutputData(
                realDataItem->intensityDataItem()->getOutputData()->clone());

    // adapting the name to job name
    realDataItemCopy->intensityDataItem()->setItemValue(IntensityDataItem::P_FILE_NAME,
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
    IntensityDataItem *intensityItem = jobItem->realDataItem()->intensityDataItem();
    DetectorItem *detector = jobItem->instrumentItem()->detectorItem();

    // removing original masks from the detector, if exists
    if(detector->maskContainerItem())
        detector->takeItem(0, DetectorItem::T_MASKS);

    if(MaskContainerItem *container = intensityItem->maskContainerItem()) {
        SessionModel *model = detector->model();
        model->copyParameterizedItem(container, detector, DetectorItem::T_MASKS);
    }
}

//! Crops RealDataItem to the region of interest. TODO is there better place?

void JobModelFunctions::cropRealData(JobItem *jobItem) {
    RealDataItem *realData = jobItem->realDataItem();

    // adjusting real data to the size of region of interest
    IntensityDataItem *intensityItem = realData->intensityDataItem();

    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*jobItem->instrumentItem());
    instrument->initDetector();

    IDetector2D::EAxesUnits requested_units
        = JobItemHelper::getAxesUnitsFromName(intensityItem->getSelectedAxesUnits());
    qDebug() << "AAAAAAa" << requested_units << intensityItem->getSelectedAxesUnits();

    std::unique_ptr<OutputData<double>> adjustedData = DetectorFunctions::createDataSet(
                *instrument.get(), *intensityItem->getOutputData(), true, requested_units);
    intensityItem->setOutputData(adjustedData.release());
    intensityItem->setAxesRangeToData();
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

