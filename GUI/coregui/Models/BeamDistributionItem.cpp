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
#include "Distributions.h"
#include "GUIHelpers.h"
#include "GroupItem.h"
#include "ParameterDistribution.h"
#include "Units.h"
#include <QDebug>

const QString BeamDistributionItem::P_DISTRIBUTION = "Distribution";

BeamDistributionItem::BeamDistributionItem(const QString name)
    : SessionItem(name)
{
    addGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    setGroupProperty(P_DISTRIBUTION, Constants::DistributionNoneType);


    mapper()->setOnChildPropertyChange(
                [this](SessionItem* item, const QString &name)
    {
        qDebug() << "AAAAA" << item->modelType() << name;
        if(item->modelType() == Constants::GroupItemType) {
            initDistributionItem();
        }
//        if (item->modelType() == Constants::IntensityDataType
//            && name == IntensityDataItem::P_AXES_UNITS) {
//            auto intensityItem = dynamic_cast<IntensityDataItem *>(item);
//            JobItemHelper::updateDataAxes(intensityItem, getInstrumentItem());
//            qDebug() << "QQQQ" << item->modelType() << name;

//        }
    });

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

//! Propagates the value stored in DistributionNone type into currently activive distribution.

void BeamDistributionItem::initDistributionItem()
{
    GroupItem *groupItem = dynamic_cast<GroupItem *>(getItem(P_DISTRIBUTION));
    Q_ASSERT(groupItem);

    SessionItem *distributionNone(0);
    foreach(SessionItem *item, groupItem->getItems(GroupItem::T_ITEMS)) {
        if(item->modelType() == Constants::DistributionNoneType) {
            distributionNone = item;
            break;
        }
    }

    if(!distributionNone)
        return;

    if(distributionNone != groupItem->currentItem()) {
        DistributionItem *distrItem = dynamic_cast<DistributionItem *>(groupItem->currentItem());
        Q_ASSERT(distrItem);
        distrItem->init_parameters(distributionNone->getItemValue(DistributionNoneItem::P_VALUE).toDouble());
    }


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
