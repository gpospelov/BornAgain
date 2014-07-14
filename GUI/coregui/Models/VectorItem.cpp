#include "VectorItem.h"

const QString VectorItem::P_TYPE_NAME = "VectorItem";
const QString VectorItem::P_X = "X";
const QString VectorItem::P_Y = "Y";
const QString VectorItem::P_Z = "Z";

VectorItem::VectorItem(ParameterizedItem *parent)
    : ParameterizedItem(P_TYPE_NAME, parent)
{
    setItemName(P_TYPE_NAME);
    registerProperty(P_X, 0.0);
    registerProperty(P_Y, 0.0);
    registerProperty(P_Z, 0.0);
}

