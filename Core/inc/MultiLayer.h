#ifndef MULTILAYER_H
#define MULTILAYER_H

#include <vector>

#include "Layer.h"
#include "LayerRoughness.h"

class MultiLayer : public ISample
{
public:
    MultiLayer();
    ~MultiLayer();

    // adds layer with top roughness
    void addLayerWithTopRoughness(Layer* p_layer, LayerRoughness* p_roughness);

    // returns number of layers in multilayer
    size_t getNumberOfLayers() const { return m_layers.size(); }

    // Overrides from ISample:
    void add(ISample* p_child);

    // returns layer with given index
    const Layer *getLayer(size_t i_layer) const { return m_layers[ check_layer_index(i_layer) ]; }

    // returns layer z-coordinate
    double getLayerZ(size_t i_layer) const { return m_layers_z[ check_layer_index(i_layer) ]; }

private:
    inline size_t check_layer_index(size_t i_layer) const { return i_layer < m_layers.size() ? i_layer : throw OutOfBoundsException("Layer index is out of bounds"); }
    std::vector<Layer*> m_layers;
    std::vector<LayerRoughness*> m_roughnesses;
    std::vector<double > m_layers_z;
};

#endif // MULTILAYER_H
