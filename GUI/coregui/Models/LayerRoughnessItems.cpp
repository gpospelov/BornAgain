#include "LayerRoughnessItems.h"
#include "ScientificDoubleProperty.h"


LayerZeroRoughnessItem::LayerZeroRoughnessItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::LayerZeroRoughnessType, parent)
{
    setItemName(Constants::LayerZeroRoughnessType);
}


const QString LayerRoughnessItem::P_SIGMA = "Sigma";
const QString LayerRoughnessItem::P_HURST = "Hurst parameter";
const QString LayerRoughnessItem::P_LATERAL_CORR_LENGTH = "Lateral corr length";

LayerRoughnessItem::LayerRoughnessItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::LayerRoughnessType, parent)
{
    setItemName(Constants::LayerRoughnessType);
    registerProperty(P_SIGMA, 1.0);
    registerProperty(P_HURST, 0.3);
    registerProperty(P_LATERAL_CORR_LENGTH, 5.0);

}
