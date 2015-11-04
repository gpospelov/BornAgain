#include "ObsoleteRectangleItem.h"

const QString ObsoleteRectangleItem::P_POSX = "X position";
const QString ObsoleteRectangleItem::P_POSY = "Y position";
const QString ObsoleteRectangleItem::P_WIDTH = "Width";
const QString ObsoleteRectangleItem::P_HEIGHT = "Height";
const QString ObsoleteRectangleItem::P_COLOR = "Color";
const QString ObsoleteRectangleItem::P_ANGLE = "Angle";

ObsoleteRectangleItem::ObsoleteRectangleItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::ObsoleteRectangleType, parent)
{
    setItemName(Constants::ObsoleteRectangleType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_COLOR, 0);
    registerProperty(P_ANGLE, 0.0);
}
