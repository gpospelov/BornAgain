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

BeamDistributionItem::BeamDistributionItem(const QString name, ParameterizedItem *parent)
    : ParameterizedItem(name, parent)
{
    registerProperty(P_CACHED_VALUE, 0.0).setHidden();
    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    setGroupProperty(P_DISTRIBUTION, Constants::DistributionNoneType);
}

void BeamDistributionItem::onPropertyChange(const QString &name)
{
    if(name == P_CACHED_VALUE) {
        DistributionItem *distribution = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION]);
        if(distribution) {
            double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
            PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
            cached_attribute.setVisible();
            // do not propagate this change back to me, or I will enter an infinite
            // signal-slot loop
            disconnect(getSubItems()[P_DISTRIBUTION], SIGNAL(propertyChanged(QString)),
                    this, SLOT(processSubItemPropertyChanged(QString)) );
            distribution->init_parameters(cached_value, cached_attribute);
            connect(getSubItems()[P_DISTRIBUTION], SIGNAL(propertyChanged(QString)),
                    this, SLOT(processSubItemPropertyChanged(QString)), Qt::UniqueConnection);
        }
    }
}

//! returns parameter distribution to add into the Simulation
std::unique_ptr<ParameterDistribution>
BeamDistributionItem::getParameterDistributionForName(const std::string &parameter_name)
{
    std::unique_ptr<ParameterDistribution> P_par_distr{};
    if (auto distributionItem
        = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
        auto P_distribution = createDistribution1D();

        if (P_distribution) {
            int nbr_samples = distributionItem->getRegisteredProperty(
                                                    DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
            double sigma_factor(0);
            if (distributionItem->isRegisteredProperty(DistributionItem::P_SIGMA_FACTOR)) {
                sigma_factor = distributionItem->getRegisteredProperty(
                                                     DistributionItem::P_SIGMA_FACTOR).toInt();
            }

            PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
            AttLimits limits;
            if (modelType() == Constants::BeamWavelengthType) {
                limits = cached_attribute.getLimits();
            } else {
                AttLimits orig = cached_attribute.getLimits();
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

//! updates new DistributionItem with cached_value
void BeamDistributionItem::onSubItemChanged(const QString &propertyName)
{
    qDebug() << "BeamWavelengthItem::onSubItemChanged(const QString &propertyName)" << propertyName;
    if(propertyName == P_DISTRIBUTION) {
        DistributionItem *distribution = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION]);
        Q_ASSERT(distribution);
        double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
        PropertyAttribute cached_attribute = getPropertyAttribute(P_CACHED_VALUE);
        cached_attribute.setVisible();
        distribution->init_parameters(cached_value, cached_attribute);
    }
    ParameterizedItem::onSubItemChanged(propertyName);
}

void BeamDistributionItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "BeamWavelengthItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)" << property_group << property_name;
    if(property_group == P_DISTRIBUTION && property_name == DistributionNoneItem::P_VALUE) {
        double value_to_cache = getSubItems()[P_DISTRIBUTION]->
                getRegisteredProperty(DistributionNoneItem::P_VALUE).toDouble();
        setRegisteredProperty(P_CACHED_VALUE, value_to_cache);
    }
    ParameterizedItem::onSubItemPropertyChanged(property_group, property_name);
}

std::unique_ptr<IDistribution1D> BeamDistributionItem::createDistribution1D()
{
    std::unique_ptr<IDistribution1D> P_distribution {};
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(
                getSubItems()[P_DISTRIBUTION])) {
        P_distribution = distributionItem->createDistribution();
    }
    return P_distribution;
}
