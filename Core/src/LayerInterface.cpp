#include "LayerInterface.h"

LayerInterface::LayerInterface() : m_LayerTop(0), m_LayerBottom(0)
{
}


LayerInterface::~LayerInterface()
{
}


LayerInterface *LayerInterface::createSmoothInterface(const Layer *p_layer_top, const Layer *p_layer_bottom)
{
    LayerInterface *lr = new LayerInterface();
    lr->setLayerTop(p_layer_top);
    lr->setLayerBottom(p_layer_bottom);
    return lr;
}


LayerInterface *LayerInterface::createRoughInterface(const Layer *p_layer_top, const Layer *p_layer_bottom, const LayerRoughness &roughness)
{
    LayerInterface *lr = new LayerInterface();
    lr->setLayerTop(p_layer_top);
    lr->setLayerBottom(p_layer_bottom);
    lr->setRoughness(roughness);
    return lr;
}

