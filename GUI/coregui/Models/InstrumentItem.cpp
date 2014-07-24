#include "InstrumentItem.h"

InstrumentItem::InstrumentItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::InstrumentType, parent)
{
    setItemName(Constants::InstrumentType);
    addToValidChildren(Constants::BeamType);
    addToValidChildren(Constants::DetectorType);
}
