// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainFittingBuilder.cpp
//! @brief     Implements class DomainFittingBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#include "DomainFittingBuilder.h"
#include "DomainSimulationBuilder.h"
#include "FitParameterItems.h"
#include "FitSuite.h"
#include "FitSuiteItem.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "IMinimizer.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "MinimizerItem.h"
#include "ModelPath.h"
#include "MultiLayerItem.h"
#include "RealDataItem.h"

// FIXME make unique_ptr all along

std::shared_ptr<FitSuite> DomainFittingBuilder::createFitSuite(JobItem *jobItem)
{
    std::shared_ptr<FitSuite> result(new FitSuite());

    FitSuiteItem *fitSuiteItem = jobItem->fitSuiteItem();
    Q_ASSERT(fitSuiteItem);

    result->setMinimizer(fitSuiteItem->minimizerContainerItem()->createMinimizer().release());

    FitParameterContainerItem *container = fitSuiteItem->fitParameterContainerItem();
    Q_ASSERT(container);

    foreach(FitParameterItem *parItem, container->fitParameterItems()) {
        double value = parItem->getItemValue(FitParameterItem::P_START_VALUE).toDouble();
        foreach(SessionItem *linkItem, parItem->getItems(FitParameterItem::T_LINK)) {
            QString link = linkItem->getItemValue(FitParameterLinkItem::P_LINK).toString();
            std::string domainPath = "*" + ModelPath::translateParameterName(jobItem, link);
            linkItem->setItemValue(FitParameterLinkItem::P_DOMAIN, QString::fromStdString(domainPath));
            result->addFitParameter(domainPath, value, parItem->getAttLimits());
            //FIXME only one link is possible at the time due to limitations in FitCore
            break;
        }
    }

    DomainSimulationBuilder builder;
    const std::unique_ptr<GISASSimulation> simulation(
                builder.getSimulation(jobItem->multiLayerItem(), jobItem->instrumentItem(),
                                      jobItem->getSimulationOptionsItem()));

    RealDataItem *realDataItem = jobItem->realDataItem();
    if(!realDataItem)
        throw GUIHelpers::Error("DomainFittingBuilder::createFitSuite() -> No Real Data defined.");

    const IntensityDataItem *intensityItem = realDataItem->intensityDataItem();
    Q_ASSERT(intensityItem);
    Q_ASSERT(intensityItem->getOutputData());

    result->addSimulationAndRealData(*simulation.get(), *intensityItem->getOutputData());

    return result;
}
