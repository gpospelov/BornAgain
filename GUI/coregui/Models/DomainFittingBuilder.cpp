// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainFittingBuilder.cpp
//! @brief     Implements class DomainFittingBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DomainFittingBuilder.h"
#include "DataItem.h"
#include "DomainSimulationBuilder.h"
#include "FitParameterItems.h"
#include "FitSuite.h"
#include "FitSuiteItem.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "IMinimizer.h"
#include "JobItem.h"
#include "MinimizerItem.h"
#include "RealDataItem.h"
#include "FitParameter.h"
#include "InstrumentItems.h"

std::shared_ptr<FitSuite> DomainFittingBuilder::createFitSuite(JobItem *jobItem)
{
    std::shared_ptr<FitSuite> result(new FitSuite);

    FitSuiteItem *fitSuiteItem = jobItem->fitSuiteItem();
    Q_ASSERT(fitSuiteItem);

    result->setMinimizer(fitSuiteItem->minimizerContainerItem()->createMinimizer().release());

    FitParameterContainerItem *container = fitSuiteItem->fitParameterContainerItem();
    Q_ASSERT(container);

    for(auto parItem : container->fitParameterItems()) {
        if(auto fitPar = parItem->createFitParameter())
            result->addFitParameter(*fitPar);
    }

    const auto simulation = DomainSimulationBuilder::createSimulation(jobItem->multiLayerItem(),
            jobItem->instrumentItem(), jobItem->simulationOptionsItem());

    RealDataItem *realDataItem = jobItem->realDataItem();
    if(!realDataItem)
        throw GUIHelpers::Error("DomainFittingBuilder::createFitSuite() -> No Real Data defined.");

    const DataItem* intensity_item = realDataItem->dataItem();
    Q_ASSERT(intensity_item);
    Q_ASSERT(intensity_item->getOutputData());

    result->addSimulationAndRealData(*simulation.get(), *intensity_item->getOutputData());

    return result;
}
