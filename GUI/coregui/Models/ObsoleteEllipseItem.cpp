#include "ObsoleteEllipseItem.h"

const QString ObsoleteEllipseItem::P_POSX = "X position";
const QString ObsoleteEllipseItem::P_POSY = "Y position";
const QString ObsoleteEllipseItem::P_WIDTH = "Width";
const QString ObsoleteEllipseItem::P_HEIGHT = "Height";
const QString ObsoleteEllipseItem::P_COLOR = "Color";
const QString ObsoleteEllipseItem::P_ANGLE = "Angle";

ObsoleteEllipseItem::ObsoleteEllipseItem(ParameterizedItem *parent)
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

