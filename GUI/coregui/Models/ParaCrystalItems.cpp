#include "ParaCrystalItems.h"


InterferenceFunction1DParaCrystalItem::InterferenceFunction1DParaCrystalItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("InterferenceFunction1DParaCrystal"), parent)
{
    setItemName("InterferenceFunction1DParaCrystal");
    setProperty("PeakDistance", 20.0);
    setProperty("Width", 7.0);
    setProperty("CorrLength", 1000.0);
}

