#ifndef MULTILAYER_H
#define MULTILAYER_H

#include <vector>

#include "layer.h"
#include "layerroughness.h"

class MultiLayer : public ISample
{
public:
    MultiLayer();
    ~MultiLayer();

    void addLayerWithTopRoughness(Layer* p_layer, LayerRoughness* p_roughness);
    size_t getNumberOfLayers() { return m_layers.size(); }

    // Overrides from ISample:
    void add(ISample* p_child);

private:
    std::vector<Layer*> m_layers;
    std::vector<LayerRoughness*> m_roughnesses;
};

#endif // MULTILAYER_H
