#include "PolygonItem.h"

const QString PolygonItem::P_COLOR = "Color";
const QString PolygonItem::P_DRAWINGMODE = "Drawing Mode";

PolygonItem::PolygonItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PolygonType, parent)
{
    setItemName(Constants::PolygonType);
    registerProperty(P_COLOR, 0);
    registerProperty(P_DRAWINGMODE, false);

    addToValidChildren(Constants::PointType);
}
