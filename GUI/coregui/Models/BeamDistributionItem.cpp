// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamDistributionItem.cpp
//! @brief     Implements class BeamDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "BeamDistributionItem.h"
#include "DistributionItem.h"
#include "Distributions.h"
#include "ParameterDistribution.h"
#include "Units.h"
#include "GUIHelpers.h"

#include <QDebug>

const QString BeamDistributionItem::P_DISTRIBUTION = "Distribution";

BeamDistributionItem::BeamDistributionItem(const QString name)
    : SessionItem(name)
{
    addGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    setGroupProperty(P_DISTRIBUTION, Constants::DistributionNoneType);
}

//! returns parameter distribution to add into the Simulation
std::unique_ptr<ParameterDistribution>
BeamDistributionItem::getParameterDistributionForName(const std::string &parameter_name)
{
    std::unique_ptr<ParameterDistribution> P_par_distr{};
    if (auto distributionItem
        = dynamic_cast<DistributionItem *>(getGroupItem(P_DISTRIBUTION))) {
        auto P_distribution = createDistribution1D();

        if (P_distribution) {
            int nbr_samples = distributionItem->getItemValue(
                                                    DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
            double sigma_factor(0);
            if (distributionItem->isTag(DistributionItem::P_SIGMA_FACTOR)) {
                sigma_factor = distributionItem->getItemValue(
                                                     DistributionItem::P_SIGMA_FACTOR).toInt();
            }
            AttLimits limits;
            SessionItem *distributionNoneValueItem =
                    getGroupItem(P_DISTRIBUTION,Constants::DistributionNoneType)->getItem(DistributionNoneItem::P_VALUE);
            if (modelType() == Constants::BeamWavelengthType) {
                limits = distributionNoneValueItem->limits();
            } else {
                AttLimits orig = distributionNoneValueItem->limits();
                if (orig.hasLowerLimit())
                    limits.setLowerLimit(Units::deg2rad(orig.getLowerLimit()));
                if (orig.hasUpperLimit())
                    limits.setUpperLimit(Units::deg2rad(orig.getUpperLimit()));
            }
            P_par_distr = GUIHelpers::make_unique<ParameterDistribution>(
                parameter_name, *P_distribution, nbr_samples, sigma_factor, limits);
        }
    }
    return P_par_distr;
}

std::unique_ptr<IDistribution1D> BeamDistributionItem::createDistribution1D()
{
    std::unique_ptr<IDistribution1D> P_distribution {};
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(
                getGroupItem(P_DISTRIBUTION))) {
        P_distribution = distributionItem->createDistribution();
    }
    return P_distribution;
}
