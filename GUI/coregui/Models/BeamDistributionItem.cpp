// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamDistributionItem.cpp
//! @brief     Implements class BeamDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
const QString BeamDistributionItem::P_CACHED_VALUE = "Cached value";

BeamDistributionItem::BeamDistributionItem(const QString name)
    : SessionItem(name)
{
    addProperty(P_CACHED_VALUE, 0.0);
    getItem(P_CACHED_VALUE)->setVisible(false);
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
            if (modelType() == Constants::BeamWavelengthType) {
                limits = getItem(P_CACHED_VALUE)->limits();
            } else {
                AttLimits orig = getItem(P_CACHED_VALUE)->limits();
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
