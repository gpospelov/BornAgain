// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainFittingBuilder.cpp
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
#include "JobItem.h"
#include "FitSuite.h"
#include "FitSuiteItem.h"
#include "FitParameterItems.h"
#include "IntensityDataItem.h"
#include "GISASSimulation.h"
#include "ModelPath.h"
#include "MultiLayerItem.h"
#include <QDebug>

std::shared_ptr<FitSuite> DomainFittingBuilder::getFitSuite(JobItem *jobItem)
{
    std::shared_ptr<FitSuite> result(new FitSuite);

    SessionItem *fitSuiteItem = jobItem->getItem(JobItem::T_FIT_SUITE);
    Q_ASSERT(fitSuiteItem);

    SessionItem *container = fitSuiteItem->getItem(FitSuiteItem::T_FIT_PARAMETERS);
    Q_ASSERT(container);

    foreach(SessionItem *parItem, container->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        double value = parItem->getItemValue(FitParameterItem::P_START_VALUE).toDouble();
        qDebug() << "FFF" << parItem->displayName() << value;

        foreach(SessionItem *linkItem, parItem->getItems(FitParameterItem::T_LINK)) {
            QString link = linkItem->getItemValue(FitParameterLinkItem::P_LINK).toString();
            std::string domainPath = "*" + ModelPath::translateParameterName(jobItem->getMultiLayerItem()->parent(), link);
            linkItem->setItemValue(FitParameterLinkItem::P_DOMAIN, QString::fromStdString(domainPath));
            result->addFitParameter(domainPath, value);
        }

    }

    DomainSimulationBuilder builder;
    const std::unique_ptr<GISASSimulation> simulation(
                builder.getSimulation(jobItem->getMultiLayerItem(),
                                        jobItem->getInstrumentItem()));

    auto x = dynamic_cast<IntensityDataItem*>(jobItem->getItem(JobItem::T_REALDATA))->getOutputData();
    if (x)
        result->addSimulationAndRealData(*simulation.get(), *x);

//    return std::move(result);
    return result;
}
