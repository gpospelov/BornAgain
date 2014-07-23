#include "RefractiveIndexItem.h"
#include "ScientificDoubleProperty.h"


const QString RefractiveIndexItem::P_DELTA = "delta_XX";
const QString RefractiveIndexItem::P_BETA = "beta_XX";


RefractiveIndexItem::RefractiveIndexItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::RefractiveIndexType, parent)
{
    setItemName(Constants::RefractiveIndexType);

    ScientificDoubleProperty delta(0.0);
    registerProperty(P_DELTA, delta.getVariant());

    ScientificDoubleProperty beta(0.0);
    registerProperty(P_BETA, beta.getVariant());
}

QString RefractiveIndexItem::getItemLabel() const
{
    return QString("(1 - %1, %2)").arg(getDelta()).arg(getBeta());
}

double RefractiveIndexItem::getDelta() const
{
    return getRegisteredProperty(P_DELTA).value<ScientificDoubleProperty>().getValue();
}

void RefractiveIndexItem::setDelta(double delta)
{
    ScientificDoubleProperty scd_property = getRegisteredProperty(P_DELTA).value<ScientificDoubleProperty>();
    scd_property.setValue(delta);
    setRegisteredProperty(P_DELTA, scd_property.getVariant());
}

double RefractiveIndexItem::getBeta() const
{
    return getRegisteredProperty(P_BETA).value<ScientificDoubleProperty>().getValue();
}

void RefractiveIndexItem::setBeta(double beta)
{
    ScientificDoubleProperty scd_property = getRegisteredProperty(P_BETA).value<ScientificDoubleProperty>();
    scd_property.setValue(beta);
    setRegisteredProperty(P_BETA, scd_property.getVariant());
}
