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
const QString BeamWavelengthItem::P_VALUE = "Value";

BeamWavelengthItem::BeamWavelengthItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamWavelengthType, parent)
{
    setItemName(Constants::BeamWavelengthType);
    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
    setGroupProperty(P_DISTRIBUTION, Constants::DistributionGateType);
    registerProperty(P_VALUE, 0.1, PropertyAttribute(AttLimits::lowerLimited(1e-4), 4));

}

void BeamWavelengthItem::onPropertyChange(const QString &name)
{
    if(name == P_DISTRIBUTION) {
        ParameterizedItem *distribution = getSubItems()[P_DISTRIBUTION];
        if(distribution) {
            if(distribution->modelType() == Constants::DistributionNoneType) {
                setPropertyAppearance(P_VALUE, PropertyAttribute::VISIBLE);
                qDebug() << "XXX setting to visible";
            } else {
                setPropertyAppearance(P_VALUE, PropertyAttribute::HIDDEN);
                qDebug() << "XXX setting to hidden";
            }
            ParameterizedItem::onPropertyChange(P_VALUE);
        }
    }
    ParameterizedItem::onPropertyChange(name);
}


const QString TestBeamItem::P_INTENSITY = "Intensity [1/s]";
const QString TestBeamItem::P_WAVELENGTH = "Wavelength";

TestBeamItem::TestBeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    registerProperty(P_INTENSITY, 1e+08);    
    registerGroupProperty(P_WAVELENGTH, Constants::BeamWavelengthType);
}


const QString BeamDistributionItem::P_DISTRIBUTION = "Distribution";
const QString BeamDistributionItem::P_VALUE = "Value";
const QString BeamDistributionItem::P_COMBO = "Combo";
const QString BeamDistributionItem::P_VECTOR = "Vector";
BeamDistributionItem::BeamDistributionItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamDistributionType, parent)
{
    qDebug() << "BeamDistributionItem::BeamDistributionItem() 1.1";
    registerGroupProperty(P_DISTRIBUTION, Constants::DistributionExtendedGroup);
//    qDebug() << "BeamDistributionItem::BeamDistributionItem() 1.2";
//    setGroupProperty(P_DISTRIBUTION, Constants::DistributionNoneType);
//    qDebug() << "BeamDistributionItem::BeamDistributionItem() 1.3";
    //setPropertyAppearance(P_DISTRIBUTION, PropertyAttribute::HIDDEN);
    qDebug() << "BeamDistributionItem::BeamDistributionItem() 1.4";
    registerProperty(P_VALUE, 99.0, PropertyAttribute(PropertyAttribute::DISABLED));

    ComboProperty types;
    types << "property 1" << "property 2" << "property 3";
    registerProperty(P_COMBO, types.getVariant());
    registerGroupProperty(P_VECTOR, Constants::VectorType);

    initProperties();
}

//void BeamDistributionItem::onPropertyChange(const QString &name)
//{
//    qDebug() << "BeamDistributionItem::onPropertyChange(const QString &name)" << name;
//    print();
//    if(name == P_DISTRIBUTION) {
//        ParameterizedItem *distribution = getSubItems()[P_DISTRIBUTION];
//        if(distribution && distribution->modelType() != Constants::DistributionNoneType) {
//            registerProperty(P_VALUE, 1.0);
//        }
//    }
//}

void BeamDistributionItem::initProperties()
{

}


