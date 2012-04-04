#ifndef LAYERROUGHNESS_H
#define LAYERROUGHNESS_H

#include "inc/Layer.h"

class LayerRoughness
{
public:
    static LayerRoughness* createSmoothLayerInterface(Layer* p_top_layer, Layer* p_bottom_layer);

protected:
    LayerRoughness();
};

#endif // LAYERROUGHNESS_H
