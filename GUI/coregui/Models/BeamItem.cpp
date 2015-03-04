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
#include <QDebug>

const QString BeamItem::P_INTENSITY = "Intensity [1/s]";
const QString BeamItem::P_WAVELENGTH = "Wavelength";
const QString BeamItem::P_INCLINATION_ANGLE = "Inclination Angle";
const QString BeamItem::P_AZIMUTHAL_ANGLE = "Azimuthal Angle";

BeamItem::BeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    ScientificDoubleProperty intensity(1e+08);
    registerProperty(P_INTENSITY, intensity.getVariant(), PropertyAttribute(AttLimits::limited(0.0, 1e+32)));

    registerGroupProperty(P_WAVELENGTH, Constants::BeamWavelengthType);
//    BeamDistributionItem *distributionItem = dynamic_cast<BeamDistributionItem *>(item);
//    distributionItem->setInitialValue(0.1, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::lowerLimited(1e-4), 4));

    registerGroupProperty(P_INCLINATION_ANGLE, Constants::BeamInclinationAngleType);
//    BeamDistributionItem *distributionItem = dynamic_cast<BeamDistributionItem *>(item);
//    distributionItem->setInitialValue(0.2, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(0.0, 90.0), 2));

    registerGroupProperty(P_AZIMUTHAL_ANGLE, Constants::BeamAzimuthalAngleType);
//    distributionItem = dynamic_cast<BeamDistributionItem *>(item);
//    distributionItem->setInitialValue(0.0, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(-90.0, 90.0), 2));
}

double BeamItem::getIntensity() const
{
    ScientificDoubleProperty intensity = getRegisteredProperty(P_INTENSITY).value<ScientificDoubleProperty>();
    return intensity.getValue();
}

void BeamItem::setIntensity(double value)
{
    ScientificDoubleProperty intensity = getRegisteredProperty(P_INTENSITY).value<ScientificDoubleProperty>();
    intensity.setValue(value);
    setRegisteredProperty(P_INTENSITY, intensity.getVariant());
}

double BeamItem::getWavelength() const
{
    ParameterizedItem *beamWavelength = getSubItems()[P_WAVELENGTH];
    Q_ASSERT(beamWavelength);
    return beamWavelength->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void BeamItem::setWavelength(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    ParameterizedItem *beamWavelength = getSubItems()[P_WAVELENGTH];
    Q_ASSERT(beamWavelength);
    ParameterizedItem *distributionItem = beamWavelength->setGroupProperty(BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
}

double BeamItem::getInclinationAngle() const
{
    ParameterizedItem *angleItem = getSubItems()[P_INCLINATION_ANGLE];
    Q_ASSERT(angleItem);
    return angleItem->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void BeamItem::setInclinationAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    ParameterizedItem *angleItem = getSubItems()[P_INCLINATION_ANGLE];
    Q_ASSERT(angleItem);
    ParameterizedItem *distributionItem = angleItem->setGroupProperty(BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
}

double BeamItem::getAzimuthalAngle() const
{
    ParameterizedItem *angleItem = getSubItems()[P_AZIMUTHAL_ANGLE];
    Q_ASSERT(angleItem);
    return angleItem->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE).toDouble();
}

void BeamItem::setAzimuthalAngle(double value, const QString &distribution_name)
{
    Q_UNUSED(distribution_name);
    ParameterizedItem *angleItem = getSubItems()[P_AZIMUTHAL_ANGLE];
    Q_ASSERT(angleItem);
    ParameterizedItem *distributionItem = angleItem->setGroupProperty(BeamDistributionItem::P_DISTRIBUTION, Constants::DistributionNoneType);
    Q_ASSERT(distributionItem);
    distributionItem->setRegisteredProperty(DistributionNoneItem::P_VALUE, value);
}

