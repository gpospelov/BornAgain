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


InterferenceFunction2DParaCrystalItem::InterferenceFunction2DParaCrystalItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("InterferenceFunction2DParaCrystal"), parent)
{
    setItemName("InterferenceFunction2DParaCrystal");
    addGroupProperty("Lattice type", "Basic");
    setProperty("Rotation_angle", 0.0);
    setProperty("Damping_length", 0.0);
    setProperty("Domain_size_1", 20.0*Units::micrometer);
    setProperty("Domain_size_2", 20.0*Units::micrometer);
    addGroupProperty("PDF #1", "Cauchy 2D");
    addGroupProperty("PDF #2", "Cauchy 2D");

}
