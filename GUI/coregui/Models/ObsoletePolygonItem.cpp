#include "ObsoletePolygonItem.h"

const QString ObsoletePolygonItem::P_COLOR = "Color";
const QString ObsoletePolygonItem::P_DRAWINGMODE = "Drawing Mode";

ObsoletePolygonItem::ObsoletePolygonItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::ObsoletePolygonType, parent)
{
    setItemName(Constants::ObsoletePolygonType);
    registerProperty(P_COLOR, 0);
    registerProperty(P_DRAWINGMODE, false);

    addToValidChildren(Constants::ObsoletePointType);
}
