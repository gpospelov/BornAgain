#include "PointItem.h"

const QString PointItem::P_POSX = "X position";
const QString PointItem::P_POSY = "Y positon";

PointItem::PointItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PointType, parent)
{
    setItemName(Constants::PointType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
}

qreal PointItem::getXPos()
{
    return getRegisteredProperty(P_POSX).toReal();
}

qreal PointItem::getYPos()
{
    return getRegisteredProperty(P_POSY).toReal();
}

void PointItem::setXPos(qreal xPos)
{
    setRegisteredProperty(P_POSX, xPos);
}

void PointItem::setYPos(qreal yPos)
{
    setRegisteredProperty(P_POSY, yPos);
}
