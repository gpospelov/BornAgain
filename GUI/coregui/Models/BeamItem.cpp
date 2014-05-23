#include "BeamItem.h"
#include "ParaCrystalItems.h"

const QString BeamItem::P_INTENSITY = "Intensity [1/s]";
const QString BeamItem::P_WAVELENGTH = "Wavelength [nm]";
const QString BeamItem::P_INCLINATION_ANGLE = "Inclination Angle";
const QString BeamItem::P_AZIMUTHAL_ANGLE = "Azimuthal Angle";

BeamItem::BeamItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Beam"), parent)
{
    setItemName("Beam");
    registerProperty(P_INTENSITY, 1000.0);
    registerProperty(P_WAVELENGTH, 0.1);
    registerProperty(P_INCLINATION_ANGLE, 0.2);
    registerProperty(P_AZIMUTHAL_ANGLE, 0.0);
    registerGroupProperty(InterferenceFunction2DParaCrystalItem::P_PDF1, "Cauchy 2D");
}

