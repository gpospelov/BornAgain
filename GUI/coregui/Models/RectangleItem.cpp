#include "RectangleItem.h"

const QString RectangleItem::P_POSX = "X position";
const QString RectangleItem::P_POSY = "y positon";
const QString RectangleItem::P_WIDTH = "Width";
const QString RectangleItem::P_HEIGHT = "Height";
const QString RectangleItem::P_COLOR = "Color";
const QString RectangleItem::P_ANGLE = "Angle";

RectangleItem::RectangleItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::RectangleType, parent)
{
    setItemName(Constants::RectangleType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_COLOR, 0);
    registerProperty(P_ANGLE, 0.0);
}
