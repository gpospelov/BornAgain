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
#include "BeamWavelengthItem.h"
#include "BeamAngleItems.h"
#include "GUIHelpers.h"
#include "Units.h"
#include "Beam.h"

const QString BeamItem::P_INTENSITY = QString::fromStdString(BornAgain::Intensity);
const QString BeamItem::P_WAVELENGTH = QString::fromStdString(BornAgain::Wavelength);
const QString BeamItem::P_INCLINATION_ANGLE = QString::fromStdString(BornAgain::Inclination);
const QString BeamItem::P_AZIMUTHAL_ANGLE = QString::fromStdString(BornAgain::Azimuth);

BeamItem::BeamItem() : SessionItem(Constants::BeamType)
{
    ScientificDoubleProperty intensity(1e+08);
    addProperty(P_INTENSITY, intensity.getVariant())->setLimits(RealLimits::limited(0.0, 1e+32))
            .setToolTip("Beam intensity in neutrons (or gammas) per sec.");
    addGroupProperty(P_WAVELENGTH, Constants::BeamWavelengthType);
    addGroupProperty(P_INCLINATION_ANGLE, Constants::BeamInclinationAngleType);
    addGroupProperty(P_AZIMUTHAL_ANGLE, Constants::BeamAzimuthalAngleType);
}

BeamItem::~BeamItem(){}

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
    BeamWavelengthItem *beamWavelength = dynamic_cast<BeamWavelengthItem *>(getItem(P_WAVELENGTH));
    return beamWavelength->wavelength();
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
    BeamInclinationAngleItem *inclination = dynamic_cast<BeamInclinationAngleItem *>(getItem(P_INCLINATION_ANGLE));
    return inclination->inclinationAngle();
}

// TODO Move down to BeamAngleItem

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
    BeamAzimuthalAngleItem *inclination = dynamic_cast<BeamAzimuthalAngleItem *>(getItem(P_AZIMUTHAL_ANGLE));
    return inclination->azimuthalAngle();
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

std::unique_ptr<Beam> BeamItem::createBeam() const
{
    auto result = GUIHelpers::make_unique<Beam>();

    result->setIntensity(getIntensity());
    double lambda = getWavelength();
    double inclination_angle = Units::deg2rad(getInclinationAngle());
    double azimuthal_angle = Units::deg2rad(getAzimuthalAngle());
    result->setCentralK(lambda, inclination_angle, azimuthal_angle);

    return std::move(result);
}
