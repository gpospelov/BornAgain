#include "LayerRoughnessItems.h"


const QString LayerZeroRoughnessItem::P_TYPE_NAME = "LayerZeroRoughness";

LayerZeroRoughnessItem::LayerZeroRoughnessItem(ParameterizedItem *parent)
    : ParameterizedItem(P_TYPE_NAME, parent)
{
    setItemName(P_TYPE_NAME);
}


const QString LayerRoughnessItem::P_TYPE_NAME = "LayerRoughness";
const QString LayerRoughnessItem::P_SIGMA = "Sigma";
const QString LayerRoughnessItem::P_HURST = "Hurst parameter";
const QString LayerRoughnessItem::P_LATERAL_CORR_LENGTH = "Lateral corr length";

LayerRoughnessItem::LayerRoughnessItem(ParameterizedItem *parent)
    : ParameterizedItem(P_TYPE_NAME, parent)
{
    setItemName(P_TYPE_NAME);
    registerProperty(P_SIGMA, 1.0);
    registerProperty(P_HURST, 0.3);
    registerProperty(P_LATERAL_CORR_LENGTH, 5.0);
}
