#include "ParaCrystalItems.h"


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
    setProperty("Length_1", 20.0);
    setProperty("Length_2", 20.0);
    setProperty("LatticeAngle", 0.0);
    setProperty("RotationAngle", 0.0);
    setProperty("DampingLength", 1000.0);
    addGroupProperty("PDF #1", "Cauchy 2D");
    addGroupProperty("PDF #2", "Cauchy 2D");

}
