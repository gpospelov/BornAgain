// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.cpp
//! @brief     Implements class BeamItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
