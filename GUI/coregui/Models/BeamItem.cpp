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
const QString BeamItem::P_ANGLE_UNITS = "Angle units";

BeamItem::BeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    setItemName(Constants::BeamType);
    registerProperty(P_INTENSITY, 1e+08);
    registerProperty(P_WAVELENGTH, 0.1);

    registerProperty(P_INCLINATION_ANGLE, AngleProperty::Degrees(0.2));
    registerProperty(P_AZIMUTHAL_ANGLE, AngleProperty::Degrees(0.1));
    registerProperty(P_ANGLE_UNITS, AngleProperty::Degrees());
}


void BeamItem::onPropertyChange(const QString &name)
{
    if(name == P_ANGLE_UNITS) {
        qDebug() << "BeamItem::onPropertyChange()" << name;
        AngleProperty angle_units_property = getRegisteredProperty(BeamItem::P_ANGLE_UNITS).value<AngleProperty>();
        qDebug() << " angle_units_property" << angle_units_property.getValue();

        AngleProperty inclination_angle = getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).value<AngleProperty>();
        inclination_angle.setUnits(angle_units_property.getUnits());
        setRegisteredProperty(P_INCLINATION_ANGLE, inclination_angle.getVariant());

        AngleProperty azimuthal_angle = getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).value<AngleProperty>();
        azimuthal_angle.setUnits(angle_units_property.getUnits());
        setRegisteredProperty(P_AZIMUTHAL_ANGLE, azimuthal_angle.getVariant());


    }
    ParameterizedItem::onPropertyChange(name);
}
