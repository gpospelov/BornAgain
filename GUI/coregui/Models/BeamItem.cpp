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
    registerProperty(P_WAVELENGTH, 0.1);
    registerProperty(P_AZIMUTHAL_ANGLE, AngleProperty::Degrees(0.0));
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
