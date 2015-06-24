#include "RectangleItem.h"

const QString RectangleItem::P_POSX = "X position";
const QString RectangleItem::P_POSY = "y positon";
const QString RectangleItem::P_WIDTH = "Width";
const QString RectangleItem::P_HEIGHT = "Height";
const QString RectangleItem::P_RESIZEMODE  = "Resize Mode";
const QString RectangleItem::P_ROTATIONMODE  = "Rotation Mode";
const QString RectangleItem::P_COLOR = "Color";

RectangleItem::RectangleItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::RectangleType, parent)
{
    setItemName(Constants::RectangleType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_RESIZEMODE, false);
    registerProperty(P_ROTATIONMODE, false);
    registerProperty(P_COLOR, 0);
}

qreal RectangleItem::getXPos()
{
    return getRegisteredProperty(P_POSX).toReal();
}

qreal RectangleItem::getYPos()
{
    return getRegisteredProperty(P_POSY).toReal();
}

qreal RectangleItem::getWidth()
{
    return getRegisteredProperty(P_WIDTH).toReal();
}

qreal RectangleItem::getHeight()
{
    return getRegisteredProperty(P_HEIGHT).toReal();
}

bool RectangleItem::isResizeMode()
{
   return getRegisteredProperty(P_RESIZEMODE).toBool();
}

bool RectangleItem::isRotationMode()
{
    return getRegisteredProperty(P_ROTATIONMODE).toBool();
}

void RectangleItem::setXPos(qreal xPos)
{
    setRegisteredProperty(P_POSX, xPos);
}

void RectangleItem::setYPos(qreal yPos)
{
    setRegisteredProperty(P_POSY, yPos);
}

void RectangleItem::setWidth(qreal width)
{
    setRegisteredProperty(P_WIDTH, width);
}

void RectangleItem::setHeight(qreal height)
{
    setRegisteredProperty(P_HEIGHT, height);
}

void RectangleItem::setResizeMode(bool resizeMode)
{
    setRegisteredProperty(P_RESIZEMODE, resizeMode);
}

void RectangleItem::setRotationMode(bool rotationMode)
{
    setRegisteredProperty(P_ROTATIONMODE, rotationMode);
}

void RectangleItem::setColor(int color)
{
    setRegisteredProperty(P_COLOR, color);
}

int RectangleItem::getColor()
{
    return getRegisteredProperty(P_COLOR).toInt();
}
