#include "ObsoletePointItem.h"

const QString ObsoletePointItem::P_POSX = "X position";
const QString ObsoletePointItem::P_POSY = "Y positon";

ObsoletePointItem::ObsoletePointItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PointType, parent)
{
    setItemName(Constants::PointType);
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
}

qreal ObsoletePointItem::getXPos()
{
    return getRegisteredProperty(P_POSX).toReal();
}

qreal ObsoletePointItem::getYPos()
{
    return getRegisteredProperty(P_POSY).toReal();
}

void ObsoletePointItem::setXPos(qreal xPos)
{
    setRegisteredProperty(P_POSX, xPos);
}

void ObsoletePointItem::setYPos(qreal yPos)
{
    setRegisteredProperty(P_POSY, yPos);
}
