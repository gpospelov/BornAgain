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
    getPropertyAttribute(BeamDistributionItem::P_CACHED_VALUE);//.setHidden();//.limited(0.0, 90.0).setDecimals(3);
    setRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE, 0.2);

    ParameterizedItem *distribution = dynamic_cast<DistributionNoneItem *>(getSubItems()[P_DISTRIBUTION]);
    Q_ASSERT(distribution);
    distribution->getPropertyAttribute(DistributionNoneItem::P_VALUE);//.limited(0.0, 90.0).setDecimals(3);
}

std::unique_ptr<IDistribution1D> BeamInclinationAngleItem::createDistribution1D()
{
    std::unique_ptr<IDistribution1D> P_distribution {};
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
        P_distribution = BeamAngleHelper::creatAngleDistribution(distributionItem);
    }
    return P_distribution;
}

// -------------------------------------------------------------------------- //

BeamAzimuthalAngleItem::BeamAzimuthalAngleItem()
    : BeamDistributionItem(Constants::BeamAzimuthalAngleType)
{
    setRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE, 0.0);
    getPropertyAttribute(BeamDistributionItem::P_CACHED_VALUE);//.setHidden();//.limited(-90.0, 90.0).setDecimals(3);
    ParameterizedItem *distribution = dynamic_cast<DistributionNoneItem *>(getSubItems()[P_DISTRIBUTION]);
    Q_ASSERT(distribution);
    distribution->getPropertyAttribute(DistributionNoneItem::P_VALUE);//.limited(-90.0, 90.0).setDecimals(3);
}

std::unique_ptr<IDistribution1D> BeamAzimuthalAngleItem::createDistribution1D()
{
    std::unique_ptr<IDistribution1D> P_distribution {};
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
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
            = distributionItem->getRegisteredProperty(DistributionGateItem::P_MIN).toDouble();
        double max
            = distributionItem->getRegisteredProperty(DistributionGateItem::P_MAX).toDouble();
        P_distribution = std::move(
            GUIHelpers::make_unique<DistributionGate>(Units::deg2rad(min), Units::deg2rad(max)));
    } else if (distributionItem->modelType() == Constants::DistributionLorentzType) {
        double mean
            = distributionItem->getRegisteredProperty(DistributionLorentzItem::P_MEAN).toDouble();
        double hwhm
            = distributionItem->getRegisteredProperty(DistributionLorentzItem::P_HWHM).toDouble();
        P_distribution = std::move(GUIHelpers::make_unique<DistributionLorentz>(
            Units::deg2rad(mean), Units::deg2rad(hwhm)));
    } else if (distributionItem->modelType() == Constants::DistributionGaussianType) {
        double mean
            = distributionItem->getRegisteredProperty(DistributionGaussianItem::P_MEAN).toDouble();
        double std_dev = distributionItem->getRegisteredProperty(
                                               DistributionGaussianItem::P_STD_DEV).toDouble();
        P_distribution = std::move(GUIHelpers::make_unique<DistributionGaussian>(
            Units::deg2rad(mean), Units::deg2rad(std_dev)));
    } else if (distributionItem->modelType() == Constants::DistributionLogNormalType) {
        double median = distributionItem->getRegisteredProperty(DistributionLogNormalItem::P_MEDIAN)
                            .toDouble();
        double scale_par = distributionItem->getRegisteredProperty(
                                                 DistributionLogNormalItem::P_SCALE_PAR).toDouble();
        P_distribution = std::move(
            GUIHelpers::make_unique<DistributionLogNormal>(Units::deg2rad(median), scale_par));
    } else if (distributionItem->modelType() == Constants::DistributionCosineType) {
        double mean
            = distributionItem->getRegisteredProperty(DistributionCosineItem::P_MEAN).toDouble();
        double sigma
            = distributionItem->getRegisteredProperty(DistributionCosineItem::P_SIGMA).toDouble();
        P_distribution = std::move(GUIHelpers::make_unique<DistributionCosine>(
            Units::deg2rad(mean), Units::deg2rad(sigma)));
    }
    return P_distribution;
}
