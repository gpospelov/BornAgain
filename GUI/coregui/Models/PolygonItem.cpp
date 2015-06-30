#include "PolygonItem.h"

const QString PolygonItem::P_COLOR = "Color";
const QString PolygonItem::P_DRAWINGMODE = "Drawing Mode";
const QString PolygonItem::P_MOUSEISOVERFIRSTPOINT = "Mouse is over first point";

PolygonItem::PolygonItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PolygonType, parent)
{
    setItemName(Constants::PolygonType);
    registerProperty(P_COLOR, 0);
    registerProperty(P_DRAWINGMODE, false);
    registerProperty(P_MOUSEISOVERFIRSTPOINT, false);

    addToValidChildren(Constants::PointType);
}

void PolygonItem::setColor(int color)
{
    setRegisteredProperty(P_COLOR, color);
}

void PolygonItem::setDrawingMode(bool drawingMode)
{
    setRegisteredProperty(P_DRAWINGMODE, drawingMode);
}

int PolygonItem::getColor()
{
    return getRegisteredProperty(P_COLOR).toInt();
}

bool PolygonItem::isDrawingMode()
{
    return getRegisteredProperty(P_DRAWINGMODE).toBool();
}
