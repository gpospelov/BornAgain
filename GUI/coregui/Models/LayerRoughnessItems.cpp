#include "LayerRoughnessItems.h"
#include "ScientificDoubleProperty.h"


LayerZeroRoughnessItem::LayerZeroRoughnessItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::LayerZeroRoughnessType, parent)
{
    setItemName(Constants::LayerZeroRoughnessType);
}


const QString LayerBasicRoughnessItem::P_SIGMA = "Sigma";
const QString LayerBasicRoughnessItem::P_HURST = "Hurst parameter";
const QString LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH = "Lateral corr length";

LayerBasicRoughnessItem::LayerBasicRoughnessItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::LayerBasicRoughnessType, parent)
{
    setItemName(Constants::LayerBasicRoughnessType);
    registerProperty(P_SIGMA, 1.0);
    registerProperty(P_HURST, 0.3);
    registerProperty(P_LATERAL_CORR_LENGTH, 5.0);

}
