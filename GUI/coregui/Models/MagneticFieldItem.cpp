#include "MagneticFieldItem.h"


const QString MagneticFieldItem::P_BX = "Bx";
const QString MagneticFieldItem::P_BY = "By";
const QString MagneticFieldItem::P_BZ = "Bz";

MagneticFieldItem::MagneticFieldItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::MagneticFieldType, parent)
{
    setItemName(Constants::MagneticFieldType);
    registerProperty(P_BX, 0.0);
    registerProperty(P_BY, 0.0);
    registerProperty(P_BZ, 0.0);
}

QString MagneticFieldItem::getItemLabel() const
{
    return QString("(%1, %2, %3)").arg(getRegisteredProperty(P_BX).toDouble())
                                  .arg(getRegisteredProperty(P_BY).toDouble())
                                  .arg(getRegisteredProperty(P_BZ).toDouble());
}



