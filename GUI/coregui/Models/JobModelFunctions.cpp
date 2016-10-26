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
#include <QDebug>

namespace JobModelFunctions {
void copyRealDataItem(JobItem *jobItem, const RealDataItem *realDataItem);
void processInstrumentLink(JobItem *jobItem);
void createFitContainers(JobItem *jobItem);
}

//! Setups JobItem for fit.

void JobModelFunctions::setupJobItemForFit(JobItem *jobItem, const RealDataItem *realDataItem)
{
    JobModelFunctions::copyRealDataItem(jobItem, realDataItem);
    JobModelFunctions::processInstrumentLink(jobItem);
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
}

//! Links RealDataItem to the JobItem's instrument.

void JobModelFunctions::processInstrumentLink(JobItem *jobItem)
{
    RealDataItem *realData = jobItem->realDataItem();
    if(!realData)
        throw GUIHelpers::Error("JobModelFunctions::processInstrumentLink() -> Error. No data.");

    InstrumentItem *instrument = jobItem->getInstrumentItem();
    if(!instrument)
        throw GUIHelpers::Error("JobModelFunctions::processInstrumentLink() -> Error. "
                                "No instrument.");

    realData->linkToInstrument(instrument);
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

