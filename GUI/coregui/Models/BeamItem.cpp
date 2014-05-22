#include "BeamItem.h"

BeamItem::BeamItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Beam"), parent)
{
    setItemName("Beam");
}

