// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamAngleItems.cpp
//! @brief     Implements class BeamAngleItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "BeamAngleItems.h"
#include "Distributions.h"
#include "Units.h"
#include "GUIHelpers.h"


BeamInclinationAngleItem::BeamInclinationAngleItem()
    : BeamDistributionItem(Constants::BeamInclinationAngleType)
{

    SessionItem *distribution = dynamic_cast<DistributionNoneItem *>(getGroupItem(P_DISTRIBUTION));
    Q_ASSERT(distribution);
    auto value = distribution->getItem(DistributionNoneItem::P_VALUE);
    value->setLimits(AttLimits::limited(0.0, 90.0));
    value->setDecimals(3);
    value->setValue(0.2);
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
    SessionItem *distribution = dynamic_cast<DistributionNoneItem *>(getGroupItem(P_DISTRIBUTION));
    Q_ASSERT(distribution);
    auto value = distribution->getItem(DistributionNoneItem::P_VALUE);
    value->setLimits(AttLimits::limited(-90.0, 90.0));
    value->setDecimals(3);
    value->setValue(0.0);
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
        P_distribution = GUIHelpers::make_unique<DistributionGate>(
                    Units::deg2rad(min), Units::deg2rad(max));
    } else if (distributionItem->modelType() == Constants::DistributionLorentzType) {
        double mean
            = distributionItem->getItemValue(DistributionLorentzItem::P_MEAN).toDouble();
        double hwhm
            = distributionItem->getItemValue(DistributionLorentzItem::P_HWHM).toDouble();
        P_distribution = GUIHelpers::make_unique<DistributionLorentz>(
                    Units::deg2rad(mean), Units::deg2rad(hwhm));
    } else if (distributionItem->modelType() == Constants::DistributionGaussianType) {
        double mean
            = distributionItem->getItemValue(DistributionGaussianItem::P_MEAN).toDouble();
        double std_dev = distributionItem->getItemValue(
                                               DistributionGaussianItem::P_STD_DEV).toDouble();
        P_distribution = GUIHelpers::make_unique<DistributionGaussian>(
                    Units::deg2rad(mean), Units::deg2rad(std_dev));
    } else if (distributionItem->modelType() == Constants::DistributionLogNormalType) {
        double median = distributionItem->getItemValue(DistributionLogNormalItem::P_MEDIAN)
                            .toDouble();
        double scale_par = distributionItem->getItemValue(
                                                 DistributionLogNormalItem::P_SCALE_PAR).toDouble();
        P_distribution = GUIHelpers::make_unique<DistributionLogNormal>(
                    Units::deg2rad(median), scale_par);
    } else if (distributionItem->modelType() == Constants::DistributionCosineType) {
        double mean
            = distributionItem->getItemValue(DistributionCosineItem::P_MEAN).toDouble();
        double sigma
            = distributionItem->getItemValue(DistributionCosineItem::P_SIGMA).toDouble();
        P_distribution = GUIHelpers::make_unique<DistributionCosine>(
                    Units::deg2rad(mean), Units::deg2rad(sigma));
    }
    return P_distribution;
}
