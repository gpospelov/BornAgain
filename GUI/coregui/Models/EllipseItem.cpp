#include "EllipseItem.h"

const QString EllipseItem::P_POSX = "X position";
const QString EllipseItem::P_POSY = "Y position";
const QString EllipseItem::P_WIDTH = "Width";
const QString EllipseItem::P_HEIGHT = "Height";
const QString EllipseItem::P_COLOR = "Color";
const QString EllipseItem::P_ANGLE = "Angle";

EllipseItem::EllipseItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::EllipseType, parent)
{
    setItemName(Constants::EllipseType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_COLOR, 0);
    registerProperty(P_ANGLE, 0.0);
}

