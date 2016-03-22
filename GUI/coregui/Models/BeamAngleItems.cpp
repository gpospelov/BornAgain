// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamWavelengthItem.cpp
//! @brief     Implements class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamAngleItems.h"
#include "item_constants.h"
#include "Distributions.h"
#include "Units.h"
#include "GUIHelpers.h"


BeamInclinationAngleItem::BeamInclinationAngleItem()
    : BeamDistributionItem(Constants::BeamInclinationAngleType)
{
    auto cache = getItem(BeamDistributionItem::P_CACHED_VALUE);
    cache->setVisible(false);
    cache->setLimits(AttLimits::limited(0.0, 90.0));
    cache->setDecimals(3);
    setItemValue(BeamDistributionItem::P_CACHED_VALUE, 0.2);

    SessionItem *distribution = dynamic_cast<DistributionNoneItem *>(getGroupItem(P_DISTRIBUTION));
    Q_ASSERT(distribution);
    auto value = distribution->getItem(DistributionNoneItem::P_VALUE);
    value->setLimits(AttLimits::limited(0.0, 90.0));
    value->setDecimals(3);
}

std::unique_ptr<IDistribution1D> BeamInclinationAngleItem::createDistribution1D()
{
    std::unique_ptr<IDistribution1D> P_distribution {};
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getGroupItem(P_DISTRIBUTION))) {
        P_distribution = BeamAngleHelper::creatAngleDistribution(distributionItem);
    }
    return P_distribution;
}

// -------------------------------------------------------------------------- //

BeamAzimuthalAngleItem::BeamAzimuthalAngleItem()
    : BeamDistributionItem(Constants::BeamAzimuthalAngleType)
{
    setItemValue(BeamDistributionItem::P_CACHED_VALUE, 0.0);
    auto cache = getItem(BeamDistributionItem::P_CACHED_VALUE);
    cache->setVisible(false);
    cache->setLimits(AttLimits::limited(-90.0, 90.0));
    cache->setDecimals(3);
    SessionItem *distribution = dynamic_cast<DistributionNoneItem *>(getGroupItem(P_DISTRIBUTION));
    Q_ASSERT(distribution);
    auto value = distribution->getItem(DistributionNoneItem::P_VALUE);
    value->setLimits(AttLimits::limited(-90.0, 90.0));
    value->setDecimals(3);
}

std::unique_ptr<IDistribution1D> BeamAzimuthalAngleItem::createDistribution1D()
{
    std::unique_ptr<IDistribution1D> P_distribution {};
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getGroupItem(P_DISTRIBUTION))) {
        P_distribution = BeamAngleHelper::creatAngleDistribution(distributionItem);
    }
    return P_distribution;
}

// -------------------------------------------------------------------------- //

std::unique_ptr<IDistribution1D>
BeamAngleHelper::creatAngleDistribution(DistributionItem *distributionItem)
{

    std::unique_ptr<IDistribution1D> P_distribution {};
    if (distributionItem->modelType() == Constants::DistributionGateType) {
        double min
            = distributionItem->getItemValue(DistributionGateItem::P_MIN).toDouble();
        double max
            = distributionItem->getItemValue(DistributionGateItem::P_MAX).toDouble();
        P_distribution = std::move(
            GUIHelpers::make_unique<DistributionGate>(Units::deg2rad(min), Units::deg2rad(max)));
    } else if (distributionItem->modelType() == Constants::DistributionLorentzType) {
        double mean
            = distributionItem->getItemValue(DistributionLorentzItem::P_MEAN).toDouble();
        double hwhm
            = distributionItem->getItemValue(DistributionLorentzItem::P_HWHM).toDouble();
        P_distribution = std::move(GUIHelpers::make_unique<DistributionLorentz>(
            Units::deg2rad(mean), Units::deg2rad(hwhm)));
    } else if (distributionItem->modelType() == Constants::DistributionGaussianType) {
        double mean
            = distributionItem->getItemValue(DistributionGaussianItem::P_MEAN).toDouble();
        double std_dev = distributionItem->getItemValue(
                                               DistributionGaussianItem::P_STD_DEV).toDouble();
        P_distribution = std::move(GUIHelpers::make_unique<DistributionGaussian>(
            Units::deg2rad(mean), Units::deg2rad(std_dev)));
    } else if (distributionItem->modelType() == Constants::DistributionLogNormalType) {
        double median = distributionItem->getItemValue(DistributionLogNormalItem::P_MEDIAN)
                            .toDouble();
        double scale_par = distributionItem->getItemValue(
                                                 DistributionLogNormalItem::P_SCALE_PAR).toDouble();
        P_distribution = std::move(
            GUIHelpers::make_unique<DistributionLogNormal>(Units::deg2rad(median), scale_par));
    } else if (distributionItem->modelType() == Constants::DistributionCosineType) {
        double mean
            = distributionItem->getItemValue(DistributionCosineItem::P_MEAN).toDouble();
        double sigma
            = distributionItem->getItemValue(DistributionCosineItem::P_SIGMA).toDouble();
        P_distribution = std::move(GUIHelpers::make_unique<DistributionCosine>(
            Units::deg2rad(mean), Units::deg2rad(sigma)));
    }
    return P_distribution;
}
