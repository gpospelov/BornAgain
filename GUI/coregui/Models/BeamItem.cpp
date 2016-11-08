// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamItem.cpp
//! @brief     Implements class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "BeamItem.h"
#include "BeamDistributionItem.h"
#include "BornAgainNamespace.h"
#include "ScientificDoubleProperty.h"


const QString BeamItem::P_INTENSITY = QString::fromStdString(BornAgain::Intensity);
const QString BeamItem::P_WAVELENGTH = QString::fromStdString(BornAgain::Wavelength);
const QString BeamItem::P_INCLINATION_ANGLE = QString::fromStdString(BornAgain::Inclination);
const QString BeamItem::P_AZIMUTHAL_ANGLE = QString::fromStdString(BornAgain::Azimuth);

BeamItem::BeamItem() : SessionItem(Constants::BeamType)
{
    ScientificDoubleProperty intensity(1e+08);
    addProperty(P_INTENSITY, intensity.getVariant())->setLimits(RealLimits::limited(0.0, 1e+32));
    addGroupProperty(P_WAVELENGTH, Constants::BeamWavelengthType);
    addGroupProperty(P_INCLINATION_ANGLE, Constants::BeamInclinationAngleType);
    addGroupProperty(P_AZIMUTHAL_ANGLE, Constants::BeamAzimuthalAngleType);
}

double BeamItem::getIntensity() const
{
    ScientificDoubleProperty intensity
        = getItemValue(P_INTENSITY).value<ScientificDoubleProperty>();
    return intensity.getValue();
}

void BeamItem::setIntensity(double value)
{
    ScientificDoubleProperty intensity
        = getItemValue(P_INTENSITY).value<ScientificDoubleProperty>();
    intensity.setValue(value);
    setItemValue(P_INTENSITY, intensity.getVariant());
}

double BeamItem::getWavelength() const
{
    SessionItem *beamWavelength = getItem(P_WAVELENGTH);
    Q_ASSERT(beamWavelength);
    SessionItem *distributionNoneValueItem =
            beamWavelength->getGroupItem(BeamDistributionItem::P_DISTRIBUTION,
                                         Constants::DistributionNoneType)
            ->getItem(DistributionNoneItem::P_VALUE);
    return distributionNoneValueItem->value().toDouble();
}

void BeamItem::setWavelength(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    SessionItem *beamWavelength = getItem(P_WAVELENGTH);
    Q_ASSERT(beamWavelength);
    SessionItem *distributionItem = beamWavelength->setGroupProperty(
        BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setItemValue(DistributionNoneItem::P_VALUE, value);
}

double BeamItem::getInclinationAngle() const
{
    SessionItem *angleItem = getItem(P_INCLINATION_ANGLE);
    Q_ASSERT(angleItem);
    SessionItem *distributionNoneValueItem =
            angleItem->getGroupItem(BeamDistributionItem::P_DISTRIBUTION,Constants::DistributionNoneType)
            ->getItem(DistributionNoneItem::P_VALUE);
    return distributionNoneValueItem->value().toDouble();
}

void BeamItem::setInclinationAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    SessionItem *angleItem = getItem(P_INCLINATION_ANGLE);
    Q_ASSERT(angleItem);
    SessionItem *distributionItem = angleItem->setGroupProperty(
        BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setItemValue(DistributionNoneItem::P_VALUE, value);
}

double BeamItem::getAzimuthalAngle() const
{
    SessionItem *angleItem = getItem(P_AZIMUTHAL_ANGLE);
    Q_ASSERT(angleItem);
    SessionItem *distributionNoneValueItem =
            angleItem->getGroupItem(BeamDistributionItem::P_DISTRIBUTION,Constants::DistributionNoneType)
            ->getItem(DistributionNoneItem::P_VALUE);
    return distributionNoneValueItem->value().toDouble();
}

void BeamItem::setAzimuthalAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    SessionItem *angleItem = getItem(P_AZIMUTHAL_ANGLE);
    Q_ASSERT(angleItem);
    SessionItem *distributionItem = angleItem->setGroupProperty(
        BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setItemValue(DistributionNoneItem::P_VALUE, value);
}
