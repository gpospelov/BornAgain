#include <algorithm>
#include <stdexcept>
#include <iomanip>

#include "MultiLayer.h"

MultiLayer::MultiLayer() : m_crossCorrLength(0)
{
    setName("multilayer");
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
    getParameterPool()->clear();
    getParameterPool()->registerParameter("crossCorrLength", &m_crossCorrLength);
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

    getParameterPool()->clear();
}


/* ************************************************************************* */
// clone MultiLayer contents including interfaces
/* ************************************************************************* */
MultiLayer *MultiLayer::clone() const
{
    MultiLayer *newMultiLayer = new MultiLayer();
    newMultiLayer->setName(getName());

    newMultiLayer->m_layers_z = m_layers_z;

    for(size_t i=0; i<m_layers.size(); i++) {
        newMultiLayer->addAndRegisterLayer( m_layers[i]->clone() );
    }

    for(size_t i=0; i<m_interfaces.size(); i++) {
        const Layer *topLayer = newMultiLayer->m_layers[i];
        const Layer *bottomLayer = newMultiLayer->m_layers[i+1];

        LayerInterface *newInterface = LayerInterface::createRoughInterface(topLayer, bottomLayer, *m_interfaces[i]->getRoughness() );
        newMultiLayer->addAndRegisterInterface( newInterface );
    }

    newMultiLayer->m_crossCorrLength = m_crossCorrLength;

    newMultiLayer->init_parameters();

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
// add layer with top roughness
/* ************************************************************************* */
void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)
{
    Layer *p_new_layer = layer.clone();
    if (getNumberOfLayers())
    {
        const Layer *p_last_layer = m_layers.back();
        LayerInterface *interface = LayerInterface::createRoughInterface( p_last_layer, p_new_layer, roughness);
        addAndRegisterLayer(p_new_layer);
        addAndRegisterInterface(interface);
        m_layers_z.push_back(m_layers_z.back() - layer.getThickness() );
        return;
    }
    addAndRegisterLayer(p_new_layer);
    m_layers_z.push_back(0.0);
}



/* ************************************************************************* */
// add layer with default (zero) roughness
/* ************************************************************************* */
void MultiLayer::addLayer(const Layer &p_child)
{
    const Layer &layer = dynamic_cast<const Layer &>(p_child);
    addLayerWithTopRoughness(layer, LayerRoughness());
}


///* ************************************************************************* */
////! Correlation function of roughnesses between the interfaces
////! j,k - indexes of layers in multilayer whose bottom interfaces we are considering
///* ************************************************************************* */
//double MultiLayer::getCrossCorrFun(const kvector_t &kvec, int j, int k) const
//{
//    double z_j = getLayerBottomZ(j);
//    double z_k = getLayerBottomZ(k);
//    const LayerRoughness &rough_j = getLayerBottomInterface(j)->getRoughness();
//    const LayerRoughness &rough_k = getLayerBottomInterface(k)->getRoughness();
//    double sigma_j = rough_j.getSigma();
//    double sigma_k = rough_k.getSigma();
//    double corr = 0.5*(sigma_k/sigma_j*rough_j.getCorrFun(kvec) + sigma_j/sigma_k*rough_k.getCorrFun(kvec) ) * std::exp( -1*std::abs(z_j-z_k)/m_crossCorrLength );
//    return corr;
//}


/* ************************************************************************* */
//! Fourier transform of the correlation function of roughnesses between the interfaces
//! j,k - indexes of layers in multilayer whose bottom interfaces we are considering
/* ************************************************************************* */
double MultiLayer::getCrossCorrSpectralFun(const kvector_t &kvec, int j, int k) const
{
    double z_j = getLayerBottomZ(j);
    double z_k = getLayerBottomZ(k);
    const LayerRoughness *rough_j = getLayerBottomInterface(j)->getRoughness();
    const LayerRoughness *rough_k = getLayerBottomInterface(k)->getRoughness();
    double sigma_j = rough_j->getSigma();
    double sigma_k = rough_k->getSigma();
    if(sigma_j == 0 || sigma_k ==0 || m_crossCorrLength==0) {
        return 0.0;
    }
    double corr = 0.5*( (sigma_k/sigma_j)*rough_j->getSpectralFun(kvec) + (sigma_j/sigma_k)*rough_k->getSpectralFun(kvec) ) * std::exp( -1*std::abs(z_j-z_k)/m_crossCorrLength );
    return corr;
}


/* ************************************************************************* */
//! change layer thickness
/* ************************************************************************* */
void MultiLayer::setLayerThickness(size_t i_layer, double thickness)
{
    m_layers[ check_layer_index(i_layer) ]->setThickness(thickness);
    // recalculating z-coordinates of layers
    m_layers_z.clear();
    m_layers_z.push_back(0.0);
    for(size_t il=1; il<getNumberOfLayers(); il++){
        m_layers_z.push_back(m_layers_z.back() - m_layers[ check_layer_index(il) ]->getThickness() );
    }
}

/* ************************************************************************* */
//! change layer thickness
/* ************************************************************************* */

MultiLayerDWBASimulation* MultiLayer::getDWBASimulation() const
{
    for (size_t i=0; i<getNumberOfLayers(); ++i) {
        LayerDWBASimulation *p_layer_dwba_sim = getLayer(i)->getDWBASimulation();
        if (p_layer_dwba_sim) {
            delete p_layer_dwba_sim;
            return new MultiLayerDWBASimulation(this);
        }
    }
    return 0;
}



/* ************************************************************************* */
// print content of multilayer
/* ************************************************************************* */
void MultiLayer::print(std::ostream &ostr) const
{
    ostr << getName() << " " << this << std::endl;

    for(size_t i=0; i<getNumberOfLayers(); i++) {
        const Layer *layer = getLayer(i);
        ostr << " " << "#" << std::left << std::setw(2) << i
             << *layer
             << std::endl;
        const LayerInterface *interface = getLayerBottomInterface(i);
        if(interface) {
            ostr << " " << "------" << *interface << std::endl;
        } else {
            ostr << " " << "------ no interface " << std::endl;
        }
    }
}
