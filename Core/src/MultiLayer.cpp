#include <algorithm>
#include <stdexcept>
#include <iomanip>

#include "MultiLayer.h"

MultiLayer::MultiLayer()
{
}


MultiLayer::~MultiLayer()
{
    clear();
}


/* ************************************************************************* */
// clear MultiLayer contents including interfaces
/* ************************************************************************* */
void MultiLayer::clear()
{
    for(size_t i=0; i<m_layers.size(); i++) {
        if( m_layers[i] ) delete m_layers[i];
    }
    m_layers.clear();

    for(size_t i=0; i<m_interfaces.size(); i++) {
        if( m_interfaces[i] ) delete m_interfaces[i];
    }
    m_interfaces.clear();

    m_layers_z.clear();
}


/* ************************************************************************* */
// clone MultiLayer contents including interfaces
/* ************************************************************************* */
MultiLayer *MultiLayer::clone() const
{
    MultiLayer *newMultiLayer = new MultiLayer();

    newMultiLayer->m_layers_z = m_layers_z;

    for(size_t i=0; i<m_layers.size(); i++) {
        newMultiLayer->m_layers.push_back( new Layer( *m_layers[i] ) );
    }

    for(size_t i=0; i<m_interfaces.size(); i++) {
        const Layer *topLayer = newMultiLayer->m_layers[i];
        const Layer *bottomLayer = newMultiLayer->m_layers[i+1];

        LayerInterface *newInterface = LayerInterface::createRoughInterface(topLayer, bottomLayer, m_interfaces[i]->getRoughness() );
        newMultiLayer->m_interfaces.push_back( newInterface );
    }

    return newMultiLayer;
}


/* ************************************************************************* */
// return pointer to the top interface of the layer
// (nInterfaces = nLayers-1, first layer in multilayer doesn't have interface)
/* ************************************************************************* */
const LayerInterface *MultiLayer::getLayerTopInterface(size_t i_layer) const
{
    return i_layer>0 ? m_interfaces[ check_interface_index(i_layer-1) ] : 0;
}


/* ************************************************************************* */
// return pointer to the bottom interface of the layer
// (nInterfaces = nLayers-1, i.e. last layer in multilayer doesn't have interface)
/* ************************************************************************* */
const LayerInterface *MultiLayer::getLayerBottomInterface(size_t i_layer) const
{
    return i_layer<m_interfaces.size() ? m_interfaces[ check_interface_index(i_layer) ] : 0;
}


/* ************************************************************************* */
// print content of multilayer on the screen
/* ************************************************************************* */
void MultiLayer::print()
{
    std::cout << "=== Multilayer =================================================" << std::endl;
    for(size_t i=0; i<getNumberOfLayers(); i++) {
        const Layer *layer = getLayer(i);
        std::cout << " " << "LAYER  "
                  << " " << "#" << std::left << std::setw(2)   << i
                  << " " << std::setw(16)  << layer
                  << " " << std::setw(5)   << layer->getThickness()
                  << " " << "z:" << std::setw(6)   << getLayerBottomZ(i)
                  << " " << std::setw(11)  << " material>"
                  << " " << (*layer->getMaterial())
                  << std::endl;
        const LayerInterface *interface = getLayerBottomInterface(i);
        std::cout << " " << "------"
                  << " " << std::setw(16)  << interface;
        if(interface) {
            std::cout << " " << " layers("
                      << " " << std::setw(16) << interface->getLayerTop()
                      << "," << std::setw(16) << interface->getLayerBottom() << ")";
        }
        std::cout << std::endl;
    }
}



/* ************************************************************************* */
// clear MultiLayer contents including interfaces
/* ************************************************************************* */
void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)
{
    Layer *p_new_layer = new Layer(layer);
    if (getNumberOfLayers())
    {
        const Layer *p_last_layer = m_layers.back();
        LayerInterface *interface = LayerInterface::createRoughInterface( p_last_layer, p_new_layer, roughness);
        m_layers.push_back( p_new_layer );
        m_interfaces.push_back(interface);
        m_layers_z.push_back(m_layers_z.back() - layer.getThickness() );
        return;
    }
    m_layers.push_back(p_new_layer);
    m_layers_z.push_back(0.0);
}


void MultiLayer::addLayer(const Layer &p_child)
{
    const Layer &layer = dynamic_cast<const Layer &>(p_child);
    addLayerWithTopRoughness(layer, LayerRoughness());
}


