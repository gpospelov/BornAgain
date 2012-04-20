#include <algorithm>
#include <stdexcept>
#include <iomanip>

#include "MultiLayer.h"

MultiLayer::MultiLayer()
{
}


//MultiLayer::MultiLayer(const MultiLayer &other) : ISample(other)
//{
//    m_layers = other.m_layers;
//    m_layers_z = other.m_layers_z;
//    m_interfaces = other.m_interfaces;
//}


//MultiLayer &MultiLayer::operator=(const MultiLayer &other)
//{
//    if( this != &other)
//    {

//        clean();
//        m_layers = other.m_layers;
//        m_layers_z = other.m_layers_z;
//        //m_interfaces = other.m_interfaces;
//    }
//    return *this;
//}


MultiLayer::~MultiLayer()
{

}


/* ************************************************************************* */
// clear MultiLayer contents including interfaces
/* ************************************************************************* */
void MultiLayer::clear()
{
    m_layers.clear();
    m_layers_z.clear();
    for(size_t i=0; i<m_interfaces.size(); i++)
    {
        if( m_interfaces[i] ) {
            delete m_interfaces[i];
            m_interfaces[i] = 0;
        }
        m_interfaces.clear();
    }
}


/* ************************************************************************* */
// clear MultiLayer contents including interfaces
/* ************************************************************************* */
MultiLayer *MultiLayer::clone()
{
//    MultiLayer
//    m_layers.clear();
//    m_layers_z.clear();
//    for(size_t i=0; i<m_interfaces.size(); i++)
//    {
//        if( m_interfaces[i] ) {
//            delete m_interfaces[i];
//            m_interfaces[i] = 0;
//        }
//        m_interfaces.clear();
//    }
    return 0;
}

const LayerInterface *MultiLayer::getLayerBottomInterface(size_t i_layer)
{
    return i_layer<m_interfaces.size() ? m_interfaces[ check_interface_index(i_layer) ] : 0;
}


const LayerInterface *MultiLayer::getLayerTopInterface(size_t i_layer)
{
    return i_layer>0 ? m_interfaces[ check_interface_index(i_layer-1) ] : 0;
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
                      << "," << std::setw(16) << interface->getLayerTop() << ")";
        }
        std::cout << std::endl;
    }
}



/* ************************************************************************* */
// clear MultiLayer contents including interfaces
/* ************************************************************************* */
void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)
{
    if (getNumberOfLayers())
    {
        //const Layer *p_last_layer = getLayer( getNumberOfLayers()-1 );
        const Layer *p_previous_layer = &m_layers[m_layers.size() -1 ];
        m_layers.push_back(layer);
        const Layer *p_new_layer = &m_layers[m_layers.size() -1 ];
        std::cout << "XXX" << p_previous_layer << " " << p_new_layer << std::endl;
        LayerInterface *interface = LayerInterface::createRoughInterface( p_previous_layer, p_new_layer, roughness);
        m_interfaces.push_back(interface);
        m_layers_z.push_back(m_layers_z.back() - layer.getThickness() );
        return;
    }
    m_layers.push_back(layer);
    m_layers_z.push_back(0.0);
}


void MultiLayer::add(const ISample &p_child)
{
    LayerRoughness defRough;
    const Layer &layer = dynamic_cast<const Layer&>(p_child);
    addLayerWithTopRoughness(layer, defRough);
}


