#include "ObsoletePolygonItem.h"

const QString ObsoletePolygonItem::P_COLOR = "Color";
const QString ObsoletePolygonItem::P_DRAWINGMODE = "Drawing Mode";

ObsoletePolygonItem::ObsoletePolygonItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PolygonType, parent)
{
    setItemName(Constants::PolygonType);
    registerProperty(P_COLOR, 0);
    registerProperty(P_DRAWINGMODE, false);

    addToValidChildren(Constants::PointType);
}
