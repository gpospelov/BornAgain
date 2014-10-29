#include "InstrumentItem.h"
#include "DetectorItems.h"
#include "BeamItem.h"

InstrumentItem::InstrumentItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::InstrumentType, parent)
{
    setItemName(Constants::InstrumentType);
    addToValidChildren(Constants::BeamType);
    addToValidChildren(Constants::DetectorType);
}


BeamItem *InstrumentItem::getBeamItem()
{
    foreach(ParameterizedItem *item, childItems()) {
        if(item->modelType() == Constants::BeamType) {
            return dynamic_cast<BeamItem *>(item);
        }
    }
    return 0;
}


DetectorItem *InstrumentItem::getDetectorItem()
{
    foreach(ParameterizedItem *item, childItems()) {
        if(item->modelType() == Constants::DetectorType) {
            return dynamic_cast<DetectorItem *>(item);
        }
    }
    return 0;
}

