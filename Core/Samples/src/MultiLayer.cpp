// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/MultiLayer.cpp
//! @brief     Implements class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <algorithm>
#include <stdexcept>
#include <iomanip>

#include "MultiLayer.h"

MultiLayer::MultiLayer() : m_crossCorrLength(0)
{
    setName("MultiLayer");
    init_parameters();
}

MultiLayer::~MultiLayer()
{
    clear();
}


/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later
// access via parameter pool
/* ************************************************************************* */
void MultiLayer::init_parameters()
{
    clearParameterPool();
    registerParameter("crossCorrLength", &m_crossCorrLength);
}

/* ************************************************************************* */
// clear MultiLayer contents including interfaces
/* ************************************************************************* */
void MultiLayer::clear()
{
    for(size_t i=0; i<m_layers.size(); i++) delete m_layers[i];
    m_layers.clear();

    for(size_t i=0; i<m_interfaces.size(); i++) delete m_interfaces[i];
    m_interfaces.clear();

    m_layers_z.clear();

    clearParameterPool();
}

//! clone MultiLayer contents including interfaces

MultiLayer *MultiLayer::clone() const
{
    MultiLayer *newMultiLayer = new MultiLayer();
    newMultiLayer->setName(getName());

    newMultiLayer->m_layers_z = m_layers_z;

    std::vector<Layer *> layer_buffer;
    for(size_t i=0; i<m_layers.size(); i++) {
        layer_buffer.push_back(m_layers[i]->clone() );
    }

    for(size_t i=0; i<m_interfaces.size(); i++) {
//        const Layer *topLayer = newMultiLayer->m_layers[i];
//        const Layer *bottomLayer = newMultiLayer->m_layers[i+1];
        const Layer *topLayer = layer_buffer[i];
        const Layer *bottomLayer = layer_buffer[i+1];

        LayerInterface *newInterface(0);
        if(m_interfaces[i]->getRoughness()) {
            newInterface = LayerInterface::createRoughInterface(topLayer,
                    bottomLayer, *m_interfaces[i]->getRoughness() );
        } else {
            newInterface = LayerInterface::createSmoothInterface(topLayer,
                    bottomLayer );
        }

        newMultiLayer->addAndRegisterLayer( layer_buffer[i] );
        newMultiLayer->addAndRegisterInterface( newInterface );
    }
    if(layer_buffer.size()) newMultiLayer->addAndRegisterLayer( layer_buffer.back() );

    newMultiLayer->m_crossCorrLength = m_crossCorrLength;

    newMultiLayer->init_parameters();

    return newMultiLayer;
}

MultiLayer* MultiLayer::cloneInvertB() const
{
    MultiLayer *newMultiLayer = new MultiLayer();
    newMultiLayer->setName(getName());

    newMultiLayer->m_layers_z = m_layers_z;

//    for(size_t i=0; i<m_layers.size(); i++) {
//        newMultiLayer->addAndRegisterLayer( m_layers[i]->cloneInvertB() );
//    }
    std::vector<Layer *> layer_buffer;
    for(size_t i=0; i<m_layers.size(); i++) {
        layer_buffer.push_back(m_layers[i]->cloneInvertB() );
    }

    for(size_t i=0; i<m_interfaces.size(); i++) {
//        const Layer *topLayer = newMultiLayer->m_layers[i];
//        const Layer *bottomLayer = newMultiLayer->m_layers[i+1];
        const Layer *topLayer = layer_buffer[i];
        const Layer *bottomLayer = layer_buffer[i+1];

        LayerInterface *newInterface(0);
        if(m_interfaces[i]->getRoughness()) {
            newInterface = LayerInterface::createRoughInterface(topLayer,
                    bottomLayer, *m_interfaces[i]->getRoughness() );
        } else {
            newInterface = LayerInterface::createSmoothInterface(topLayer,
                    bottomLayer );
        }
        newMultiLayer->addAndRegisterLayer( layer_buffer[i] );
        newMultiLayer->addAndRegisterInterface( newInterface );
    }
    if(layer_buffer.size()) newMultiLayer->addAndRegisterLayer( layer_buffer.back() );

    newMultiLayer->m_crossCorrLength = m_crossCorrLength;

    newMultiLayer->init_parameters();

    return newMultiLayer;
}

//! Returns pointer to the top interface of the layer.
//! nInterfaces = nLayers-1, first layer in multilayer doesn't have interface.
const LayerInterface *MultiLayer::getLayerTopInterface(size_t i_layer) const
{
    return i_layer>0 ? m_interfaces[ check_interface_index(i_layer-1) ] : 0;
}

//! Returns pointer to the bottom interface of the layer.
const LayerInterface *MultiLayer::getLayerBottomInterface(size_t i_layer) const
{
    return i_layer<m_interfaces.size() ?
        m_interfaces[ check_interface_index(i_layer) ] : 0;
}

//! Adds layer with top roughness

void MultiLayer::addLayerWithTopRoughness(
    const Layer& layer, const LayerRoughness& roughness)
{
    Layer *p_new_layer = layer.clone();
    if (getNumberOfLayers())
    {
        const Layer *p_last_layer = m_layers.back();
        LayerInterface *interface =
            LayerInterface::createRoughInterface(
                p_last_layer, p_new_layer, roughness);
        addAndRegisterInterface(interface);
        addAndRegisterLayer(p_new_layer);
        m_layers_z.push_back(m_layers_z.back() - layer.getThickness() );
        return;
    }
    addAndRegisterLayer(p_new_layer);
    m_layers_z.push_back(0.0);
}

//! Adds layer with default (zero) roughness

void MultiLayer::addLayer(const Layer& layer)
{
    LayerRoughness zero_roughness;
    addLayerWithTopRoughness(layer, zero_roughness);
}


//! Fourier transform of the correlation function of roughnesses between the interfaces
//! j,k - indexes of layers in multilayer whose bottom interfaces we are considering

double MultiLayer::getCrossCorrSpectralFun(const kvector_t& kvec, size_t j, size_t k) const
{
    if(m_crossCorrLength == 0) return 0.0;
    double z_j = getLayerBottomZ(j);
    double z_k = getLayerBottomZ(k);
    const LayerRoughness *rough_j = getLayerBottomInterface(j)->getRoughness();
    const LayerRoughness *rough_k = getLayerBottomInterface(k)->getRoughness();
    if( !rough_j || !rough_k ) return 0.0;
    double sigma_j = rough_j->getSigma();
    double sigma_k = rough_k->getSigma();
    if(sigma_j == 0 || sigma_k == 0) return 0.0;
    double corr = 0.5*( (sigma_k/sigma_j)*rough_j->getSpectralFun(kvec) +
                        (sigma_j/sigma_k)*rough_k->getSpectralFun(kvec) ) *
        std::exp( -1*std::abs(z_j-z_k)/m_crossCorrLength );
    return corr;
}

//! Changes layer thickness.

void MultiLayer::setLayerThickness(size_t i_layer, double thickness)
{
    if (thickness < 0.)
        throw DomainErrorException("Layer thickness cannot be negative");

    m_layers[ check_layer_index(i_layer) ]->setThickness(thickness);
    // recalculating z-coordinates of layers
    m_layers_z.clear();
    m_layers_z.push_back(0.0);
    for(size_t il=1; il<getNumberOfLayers(); il++){
        m_layers_z.push_back(
            m_layers_z.back() -
            m_layers[ check_layer_index(il) ]->getThickness() );
    }
}


MultiLayerDWBASimulation* MultiLayer::createDWBASimulation() const
{
    for (size_t i=0; i<getNumberOfLayers(); ++i) {
        if( getLayer(i)->hasDWBASimulation() )
            return new MultiLayerDWBASimulation(this);
    }

    for(size_t i=0; i<getNumberOfInterfaces(); ++i) {
        if( getLayerInterface(i)->getRoughness() )
            return new MultiLayerDWBASimulation(this);
    }
    return 0;
}

int MultiLayer::getIndexOfLayer(const Layer *layer) const
{
    for (size_t i=0; i<getNumberOfLayers(); ++i) {
        if(layer == m_layers[i]) return i;
    }
    return -1;
}

void MultiLayer::print(std::ostream& ostr) const
{
    ostr << "MultiLayer:" << getName() << "<" << this << "> : {\n";
    for(size_t i=0; i<getNumberOfLayers(); i++) {
        ostr << " layer " << std::left << std::setw(2) << i << " { "
             << *getLayer(i) << " }\n";
        const LayerInterface *interface = getLayerBottomInterface(i);
        if(interface) {
            ostr << " int.face {" << *interface << " }\n";
        } else {
            ostr << " int.face: NONE" << "\n";
        }
    }
    ostr << "}";
}

void MultiLayer::setNLayersInLayers() const
{
    size_t n_layers = getNumberOfLayers();
    for (size_t i=0; i<getNumberOfLayers(); ++i) {
        m_layers[i]->setNumberOfLayers(n_layers);
    }
}


bool MultiLayer::requiresMatrixRTCoefficients() const
{
    for (size_t i=0; i<this->getNumberOfLayers(); ++i) {
        const Layer *p_layer = this->getLayer(i);
        const IMaterial *p_material = p_layer->getMaterial();
        if (!p_material->isScalarMaterial()) return true;
    }
    return false;
}

size_t MultiLayer::zToLayerIndex(double z_value)
{
    if(z_value < m_layers_z.back()) return m_layers_z.size()-1;
    std::vector<double>::reverse_iterator top_limit = std::upper_bound(m_layers_z.rbegin(), m_layers_z.rend(), z_value);
    size_t nbin = m_layers_z.rend() - top_limit;
    return nbin;
}

