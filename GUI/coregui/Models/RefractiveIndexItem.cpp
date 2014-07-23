#include "RefractiveIndexItem.h"


const QString RefractiveIndexItem::P_DELTA = "delta";
const QString RefractiveIndexItem::P_BETA = "beta";


RefractiveIndexItem::RefractiveIndexItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::RefractiveIndexType, parent)
{
    setItemName(Constants::RefractiveIndexType);
    registerProperty(P_DELTA, 0.0);
    registerProperty(P_BETA, 0.0);
}

QString RefractiveIndexItem::getItemLabel() const
{
    return QString("(1 - %1, %2)").arg(getRegisteredProperty(P_DELTA).toDouble())
            .arg(getRegisteredProperty(P_BETA).toDouble());
}

double RefractiveIndexItem::getDelta() const
{
    return getRegisteredProperty(P_DELTA).toDouble();

}

double RefractiveIndexItem::getBeta() const
{
    return getRegisteredProperty(P_BETA).toDouble();
}
