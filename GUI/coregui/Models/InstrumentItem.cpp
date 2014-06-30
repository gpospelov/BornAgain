#include "InstrumentItem.h"

InstrumentItem::InstrumentItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Instrument"), parent)
{
    setItemName("Instrument");
    addToValidChildrenX(QString("Beam"));
    addToValidChildrenX(QString("Detector"));
}
