#include "EllipseItem.h"

const QString EllipseItem::P_POSX = "X position";
const QString EllipseItem::P_POSY = "y positon";
const QString EllipseItem::P_WIDTH = "Width";
const QString EllipseItem::P_HEIGHT = "Height";
const QString EllipseItem::P_RESIZEMODE  = "Resize Mode";
const QString EllipseItem::P_ROTATIONMODE  = "Rotation Mode";
const QString EllipseItem::P_COLOR = "Color";

EllipseItem::EllipseItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::EllipseType, parent)
{
    setItemName(Constants::EllipseType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_RESIZEMODE, false);
    registerProperty(P_ROTATIONMODE, false);
    registerProperty(P_COLOR, 0);
}

qreal EllipseItem::getXPos()
{
    return getRegisteredProperty(P_POSX).toReal();
}

qreal EllipseItem::getYPos()
{
    return getRegisteredProperty(P_POSY).toReal();
}

qreal EllipseItem::getWidth()
{
    return getRegisteredProperty(P_WIDTH).toReal();
}

qreal EllipseItem::getHeight()
{
    return getRegisteredProperty(P_HEIGHT).toReal();
}

bool EllipseItem::isResizeMode()
{
   return getRegisteredProperty(P_RESIZEMODE).toBool();
}

bool EllipseItem::isRotationMode()
{
    return getRegisteredProperty(P_ROTATIONMODE).toBool();
}

void EllipseItem::setXPos(qreal xPos)
{
    setRegisteredProperty(P_POSX, xPos);
}

void EllipseItem::setYPos(qreal yPos)
{
    setRegisteredProperty(P_POSY, yPos);
}

void EllipseItem::setWidth(qreal width)
{
    setRegisteredProperty(P_WIDTH, width);
}

void EllipseItem::setHeight(qreal height)
{
    setRegisteredProperty(P_HEIGHT, height);
}

void EllipseItem::setResizeMode(bool resizeMode)
{
    setRegisteredProperty(P_RESIZEMODE, resizeMode);
}

void EllipseItem::setRotationMode(bool rotationMode)
{
    setRegisteredProperty(P_ROTATIONMODE, rotationMode);
}

void EllipseItem::setColor(int color)
{
    setRegisteredProperty(P_COLOR, color);
}

int EllipseItem::getColor()
{
    return getRegisteredProperty(P_COLOR).toInt();
}
