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
const QString BeamItem::P_AZIMUTHAL_ANGLE2 = "Azimuthal Angle 2";
const QString BeamItem::P_INCLINATION_ANGLE2 = "Inclination Angle 2";

BeamItem::BeamItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::BeamType, parent)
{
    setItemName(Constants::BeamType);
    registerProperty(P_INTENSITY, 1e+08);
    registerProperty(P_WAVELENGTH, 0.1);

    registerProperty(P_INCLINATION_ANGLE, 0.2);
    registerProperty(P_AZIMUTHAL_ANGLE, 0.0);

    AngleProperty inclination_angle(0.2, AngleProperty::Degrees);
    registerProperty(P_INCLINATION_ANGLE2, inclination_angle.getVariant());

    ComboProperty units;
    units << "Degrees" << "Radians";
    registerProperty(P_ANGLE_UNITS, units.getVariant());

}


void BeamItem::onPropertyChange(const QString &name)
{
    if(name == P_ANGLE_UNITS) {
        qDebug() << "BeamItem::onPropertyChange()" << name;
        ComboProperty angle_units_property = getRegisteredProperty(BeamItem::P_ANGLE_UNITS).value<ComboProperty>();
        qDebug() << " angle_units_property" << angle_units_property.getValue();

        AngleProperty inclination_angle = getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE2).value<AngleProperty>();
        if(angle_units_property.getValue() == "Degrees") {
            inclination_angle.setInDegrees();
        } else {
            inclination_angle.setInRadians();
        }
        setRegisteredProperty(P_INCLINATION_ANGLE2, inclination_angle.getVariant());



//        if(angle_units_property.getValue() == "Degrees") {

//        }

    }
    ParameterizedItem::onPropertyChange(name);
}
