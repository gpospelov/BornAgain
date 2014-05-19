#include "ParaCrystalItems.h"
#include "Units.h"


InterferenceFunction1DParaCrystalItem::InterferenceFunction1DParaCrystalItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("InterferenceFunction1DParaCrystal"), parent)
{
    setItemName("InterferenceFunction1DParaCrystal");
    setProperty("PeakDistance", 20.0);
    setProperty("Width", 7.0);
    setProperty("CorrLength", 1000.0);
}


const QString InterferenceFunction2DParaCrystalItem::P_LATTICE_TYPE = "Lattice type";
const QString InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE = "Rotation_angle";

InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("InterferenceFunction2DParaCrystal"), parent)
{
    setItemName("InterferenceFunction2DParaCrystal");
    registerGroupProperty(P_LATTICE_TYPE, "Basic");

    registerProperty(P_ROTATION_ANGLE, 0.0);
    registerProperty("Damping_length", 0.0);
    registerProperty("Domain_size_1",
                     20.0*Units::micrometer,
                     "Dimension of coherent domains of the paracrystal along the main X axis."
                     );
    registerProperty("Domain_size_2",
                     20.0*Units::micrometer,
                     "Dimension of coherent domains of the paracrystal along the main Y axis."
                     );
    registerProperty("IntegrationOverXi", true);
    registerGroupProperty("PDF #1", "Cauchy 2D");
    registerGroupProperty("PDF #2", "Cauchy 2D");
}
