#include <algorithm>
#include <stdexcept>

#include "MultiLayer.h"

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
        m_layers_z.push_back(m_layers_z.back() - p_layer->getThickness() );
        return;
    }
    m_layers.push_back(p_layer);
    m_layers_z.push_back(0.0);
}


void MultiLayer::add(ISample* p_child)
{
    Layer* p_layer = dynamic_cast<Layer*>(p_child);
    addLayerWithTopRoughness(p_layer, 0);
}


