#include <algorithm>
#include <stdexcept>

#include "multilayer.h"

MultiLayer::MultiLayer()
{
}

MultiLayer::~MultiLayer()
{
}

void MultiLayer::addLayerWithTopRoughness(Layer *p_layer, LayerRoughness *p_roughness)
{
    if (!p_layer)
    {
        throw NullPointerException("The layer to add does not exist.");
    }
    if (getNumberOfLayers())
    {
        Layer* p_last_layer = dynamic_cast<Layer*>(m_layers[getNumberOfLayers()-1]);
        LayerRoughness* p_top_roughness = p_roughness;
        if (!p_top_roughness)
        {
            p_top_roughness = LayerRoughness::createSmoothLayerInterface(p_last_layer, p_layer);
        }
        m_layers.push_back(p_layer);
        m_roughnesses.push_back(p_top_roughness);
        return;
    }
    m_layers.push_back(p_layer);
}

void MultiLayer::add(ISample* p_child)
{
    Layer* p_layer = dynamic_cast<Layer*>(p_child);
    addLayerWithTopRoughness(p_layer, 0);
}
