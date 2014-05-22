#include "DetectorItem.h"

DetectorItem::DetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Detector"), parent)
{
    setItemName("Detector");
}
