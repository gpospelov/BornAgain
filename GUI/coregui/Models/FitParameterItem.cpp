#include "FitParameterItem.h"

const QString FitParameterItem::P_MIN = "Min";

FitParameterItem::FitParameterItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterType, parent)
{
    setItemName(Constants::FitParameterType);
    registerProperty(P_MIN, 0.0);
}


