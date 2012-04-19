#include <algorithm>
#include <stdexcept>

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
//    MultiLayer *newML = new MultiLayer;
//    newML->m_layers = m_layers;
//    newML->m_layers_z = m_layers_z;
//    for(size_t i=0; i<m_interfaces.size(); i++) {

//    }
//    newMl->m_interfaces.resize(m_layers.)
    return 0;
}



/* ************************************************************************* */
// clear MultiLayer contents including interfaces
/* ************************************************************************* */
void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)
{
    if (getNumberOfLayers())
    {
        //const Layer *p_last_layer = getLayer( getNumberOfLayers()-1 );
        const Layer *p_previous_layer = &m_layers.back();
        m_layers.push_back(layer);
        const Layer *p_new_layer = &m_layers.back();
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


