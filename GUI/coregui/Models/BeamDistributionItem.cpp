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
#include "ParameterDistribution.h"
#include <QDebug>
#include <boost/scoped_ptr.hpp>


const QString BeamDistributionItem::P_DISTRIBUTION = "Distribution";
const QString BeamDistributionItem::P_CACHED_VALUE = "Cached value";

BeamDistributionItem::BeamDistributionItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamDistributionType, parent)
{
    setItemName(Constants::BeamDistributionType);
    registerProperty(P_CACHED_VALUE, 0.0, PropertyAttribute(PropertyAttribute::HIDDEN));
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
            cached_attribute.setAppearance(PropertyAttribute::VISIBLE);
            distribution->init_parameters(cached_value, cached_attribute);
        }
    }
}

void BeamDistributionItem::setInitialValue(double value, const PropertyAttribute &attribute)
{
    PropertyAttribute cached_attribute = attribute;
    cached_attribute.setAppearance(PropertyAttribute::HIDDEN);
    setPropertyAttribute(P_CACHED_VALUE, cached_attribute);
    setRegisteredProperty(P_CACHED_VALUE, value);
}

//! returns parameter distribution to add into the Simulation
ParameterDistribution *BeamDistributionItem::getParameterDistributionForName(const QString &parameter_name)
{
    ParameterDistribution *result(0);
    if(DistributionItem *distributionItem = dynamic_cast<DistributionItem *>(getSubItems()[P_DISTRIBUTION])) {
        boost::scoped_ptr<IDistribution1D> distribution(distributionItem->createDistribution());

        if(distribution) {
            int nbr_samples = distributionItem->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
            double sigma_factor = distributionItem->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toInt();
            result = new ParameterDistribution(parameter_name.toStdString(), *distribution, nbr_samples, sigma_factor);
        }
    }
    return result;
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
        cached_attribute.setAppearance(PropertyAttribute::VISIBLE);
        distribution->init_parameters(cached_value, cached_attribute);
    }
    ParameterizedItem::onSubItemChanged(propertyName);
}

void BeamDistributionItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "BeamWavelengthItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)" << property_group << property_name;
    if(property_group == P_DISTRIBUTION && property_name == DistributionNoneItem::P_VALUE) {
        double value_to_cache = getSubItems()[P_DISTRIBUTION]->getRegisteredProperty(DistributionNoneItem::P_VALUE).toDouble();
        setRegisteredProperty(P_CACHED_VALUE, value_to_cache);
    }
    ParameterizedItem::onSubItemPropertyChanged(property_group, property_name);
}


