#include "ParaCrystalItems.h"
#include "Units.h"


const QString InterferenceFunction1DParaCrystalItem::P_PEAK_DISTANCE =
        "Peak_distance";
const QString InterferenceFunction1DParaCrystalItem::P_DAMPING_LENGTH =
        "Damping_length";
const QString InterferenceFunction1DParaCrystalItem::P_DOMAIN_SIZE =
        "Domain_size";
const QString InterferenceFunction1DParaCrystalItem::P_KAPPA =
        "Size_space_coupling";
const QString InterferenceFunction1DParaCrystalItem::P_PDF = "PDF";

const QString InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE =
        "Lattice_type";
const QString InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE =
        "Rotation_angle";
const QString InterferenceFunction2DParaCrystalItem::P_DAMPING_LENGTH =
        "Damping_length";
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE1 =
        "Domain_size_1";
const QString InterferenceFunction2DParaCrystalItem::P_DOMAIN_SIZE2 =
        "Domain_size_2";
const QString InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION =
        "Integration_over_xi";
const QString InterferenceFunction2DParaCrystalItem::P_PDF1 = "PDF #1";
const QString InterferenceFunction2DParaCrystalItem::P_PDF2 = "PDF #2";


InterferenceFunction1DParaCrystalItem::InterferenceFunction1DParaCrystalItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("InterferenceFunction1DParaCrystal"),
                                parent)
{
    setItemName("InterferenceFunction1DParaCrystal");
    registerProperty(P_PEAK_DISTANCE, 20.0*Units::nanometer);
    registerProperty(P_DAMPING_LENGTH, 1000.0*Units::micrometer);
    registerProperty(P_DOMAIN_SIZE, 20.0*Units::micrometer);
    registerProperty(P_KAPPA, 0.0);
    registerGroupProperty(P_PDF, "Gauss 1D");
}


InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem(
        ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("InterferenceFunction2DParaCrystal"),
                                parent)
{
    setItemName("InterferenceFunction2DParaCrystal");
    registerGroupProperty(P_LATTICE_TYPE, "Basic");

    registerProperty(P_DAMPING_LENGTH, 0.0);
    registerProperty(P_DOMAIN_SIZE1, 20.0*Units::micrometer);
    registerProperty(P_DOMAIN_SIZE2, 20.0*Units::micrometer);
    registerProperty(P_ROTATION_ANGLE, 0.0);
    registerProperty(P_XI_INTEGRATION, true);
    registerGroupProperty(P_PDF1, "Cauchy 2D");
    registerGroupProperty(P_PDF2, "Cauchy 2D");
}


void InterferenceFunction2DParaCrystalItem::onPropertyChange(const QString &name)
{
    if(name == P_XI_INTEGRATION) {
        if(getRegisteredProperty(P_XI_INTEGRATION).toBool()) {
            setPropertyAttribute(P_ROTATION_ANGLE, ParameterizedItem::DisabledProperty);
        } else {
            setPropertyAttribute(P_ROTATION_ANGLE, ParameterizedItem::DefaultAttribute);
        }
    }
    emit propertyChanged(P_ROTATION_ANGLE);
    emit propertyChanged(name);
}
