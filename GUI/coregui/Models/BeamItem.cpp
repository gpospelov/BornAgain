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
#include "Units.h"
#include <QDebug>

const QString BeamItem::P_INTENSITY = "Intensity [1/s]";
const QString BeamItem::P_WAVELENGTH = "Wavelength [nm]";
const QString BeamItem::P_INCLINATION_ANGLE = "Inclination Angle";
const QString BeamItem::P_AZIMUTHAL_ANGLE = "Azimuthal Angle";

BeamItem::BeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    setItemName(Constants::BeamType);
    registerProperty(P_INTENSITY, 1e+08);
    registerProperty(P_WAVELENGTH, 0.1, PropertyAttribute(AttLimits::lowerLimited(1e-4), 4));
    registerProperty(P_AZIMUTHAL_ANGLE, AngleProperty::Degrees(0.0), PropertyAttribute(AttLimits::limited(-90.0, 90.0), 3));
    registerProperty(P_INCLINATION_ANGLE, AngleProperty::Degrees(0.2));
}


void BeamItem::onPropertyChange(const QString &name)
{
    if(name == P_INCLINATION_ANGLE) {
        qDebug() << "BeamItem::onPropertyChange()" << name;
        AngleProperty inclination_angle = getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).value<AngleProperty>();

        AngleProperty azimuthal_angle = getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).value<AngleProperty>();
        azimuthal_angle.setUnits(inclination_angle.getUnits());
        setRegisteredProperty(P_AZIMUTHAL_ANGLE, azimuthal_angle.getVariant());
    }
    ParameterizedItem::onPropertyChange(name);
}

// ---------------


const QString BeamWavelengthItem::P_DISTRIBUTION = "Distribution";
const QString BeamWavelengthItem::P_CACHED_VALUE = "Value";

BeamWavelengthItem::BeamWavelengthItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamWavelengthType, parent)
{
    setItemName(Constants::BeamWavelengthType);
    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    setGroupProperty(P_DISTRIBUTION, Constants::DistributionGateType);
    registerProperty(P_CACHED_VALUE, 0.1, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::lowerLimited(1e-4), 4));

}

//void BeamWavelengthItem::onPropertyChange(const QString &name)
//{
//    qDebug() << " ";
//    qDebug() << " ";
//    qDebug() << " ";
//    qDebug() << " ";
//    qDebug() << "BeamWavelengthItem::onPropertyChange(const QString &name)" << name;

//    if(name == P_DISTRIBUTION) {
//        ParameterizedItem *distribution = getSubItems()[P_DISTRIBUTION];
//        if(distribution) {
//            if(distribution->modelType() == Constants::DistributionNoneType) {
//                setPropertyAppearance(P_CACHED_VALUE, PropertyAttribute::VISIBLE);
//                qDebug() << "XXX setting to visible";
//            } else {
//                setPropertyAppearance(P_CACHED_VALUE, PropertyAttribute::HIDDEN);
//                qDebug() << "XXX setting to hidden";
//            }
//            ParameterizedItem::onPropertyChange(P_CACHED_VALUE);
//        }
//    }
//    ParameterizedItem::onPropertyChange(name);
//}

void BeamWavelengthItem::onSubItemChanged(const QString &propertyName)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << "BeamWavelengthItem::onSubItemChanged(const QString &propertyName)" << propertyName;
    if(propertyName == P_DISTRIBUTION) {
        ParameterizedItem *distribution = getSubItems()[P_DISTRIBUTION];
        Q_ASSERT(distribution);
        if(distribution->modelType() == Constants::DistributionNoneType) {
            double cached_value = getRegisteredProperty(P_CACHED_VALUE).toDouble();
            distribution->setRegisteredProperty(DistributionNoneItem::P_VALUE, cached_value);
            distribution->setPropertyAttribute(DistributionNoneItem::P_VALUE, PropertyAttribute(AttLimits::lowerLimited(1e-4), 4));
        }
    }
    ParameterizedItem::onSubItemChanged(propertyName);
}

void BeamWavelengthItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "OOO";
    qDebug() << "OOO";
    qDebug() << "OOO";
    qDebug() << "OOO";
    qDebug() << "BeamWavelengthItem::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)" << property_group << property_name;
    if(property_group == P_DISTRIBUTION && property_name == DistributionNoneItem::P_VALUE) {
        double value_to_cache = getSubItems()[P_DISTRIBUTION]->getRegisteredProperty(DistributionNoneItem::P_VALUE).toDouble();
        setRegisteredProperty(P_CACHED_VALUE, value_to_cache);
    }
}




const QString TestBeamItem::P_INTENSITY = "Intensity [1/s]";
const QString TestBeamItem::P_WAVELENGTH = "Wavelength";

TestBeamItem::TestBeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    registerProperty(P_INTENSITY, 1e+08);    
    registerGroupProperty(P_WAVELENGTH, Constants::BeamWavelengthType);
}
