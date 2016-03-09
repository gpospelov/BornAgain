// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.cpp
//! @brief     Implements class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamItem.h"
#include "InterferenceFunctionItems.h"
#include "ComboProperty.h"
#include "AngleProperty.h"
#include "DistributionItem.h"
#include "ScientificDoubleProperty.h"
#include "BeamDistributionItem.h"
#include "Units.h"
#include "BeamDistributionItem.h"
#include "BornAgainNamespace.h"

#include <QDebug>

const QString BeamItem::P_INTENSITY = QString::fromStdString(BornAgain::Intensity);
const QString BeamItem::P_WAVELENGTH = QString::fromStdString(BornAgain::Wavelength);
const QString BeamItem::P_INCLINATION_ANGLE = "Inclination Angle";
const QString BeamItem::P_AZIMUTHAL_ANGLE = "Azimuthal Angle";

BeamItem::BeamItem() : SessionItem(Constants::BeamType)
{
    ScientificDoubleProperty intensity(1e+08);
    addProperty(P_INTENSITY, intensity.getVariant())->setLimits(AttLimits::limited(0.0, 1e+32));
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
    SessionItem *beamWavelength = getGroupItem(P_WAVELENGTH);
    Q_ASSERT(beamWavelength);
    return beamWavelength->getItemValue(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void BeamItem::setWavelength(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    SessionItem *beamWavelength = getGroupItem(P_WAVELENGTH);
    Q_ASSERT(beamWavelength);
    SessionItem *distributionItem = beamWavelength->setGroupProperty(
        BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setItemValue(DistributionNoneItem::P_VALUE, value);
}

double BeamItem::getInclinationAngle() const
{
    SessionItem *angleItem = getGroupItem(P_INCLINATION_ANGLE);
    Q_ASSERT(angleItem);
    return angleItem->getItemValue(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void BeamItem::setInclinationAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    SessionItem *angleItem = getGroupItem(P_INCLINATION_ANGLE);
    Q_ASSERT(angleItem);
    SessionItem *distributionItem = angleItem->setGroupProperty(
        BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setItemValue(DistributionNoneItem::P_VALUE, value);
}

double BeamItem::getAzimuthalAngle() const
{
    SessionItem *angleItem = getGroupItem(P_AZIMUTHAL_ANGLE);
    Q_ASSERT(angleItem);
    return angleItem->getItemValue(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void BeamItem::setAzimuthalAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    SessionItem *angleItem = getGroupItem(P_AZIMUTHAL_ANGLE);
    Q_ASSERT(angleItem);
    SessionItem *distributionItem = angleItem->setGroupProperty(
        BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setItemValue(DistributionNoneItem::P_VALUE, value);
}
