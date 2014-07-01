#include "InstrumentItem.h"

InstrumentItem::InstrumentItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Instrument"), parent)
{
    setItemName("Instrument");
    addToValidChildren(QString("Beam"));
    addToValidChildren(QString("Detector"));
}
