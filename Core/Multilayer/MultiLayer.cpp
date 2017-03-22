// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayer.cpp
//! @brief     Implements class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayer.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "ILayout.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "HomogeneousMaterial.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include <iomanip>

MultiLayer::MultiLayer() : m_crossCorrLength(0)
{
    setName(BornAgain::MultiLayerType);
    init_parameters();
}

MultiLayer::~MultiLayer()
{
    clear();
}

void MultiLayer::init_parameters()
{
    getParameterPool()->clear(); // non-trivially needed
    registerParameter(BornAgain::CrossCorrelationLength, &m_crossCorrLength).
        setUnit("nm").setNonnegative();
}

const ILayout * MultiLayer::layout(size_t i) const
{
    if (i >= m_layouts.size())
        return nullptr;
    return m_layouts[i];
}

void MultiLayer::clear() // TODO: understand need
{
    for (size_t i=0; i<m_layers.size(); i++)
        delete m_layers[i];
    m_layers.clear();

    for (size_t i=0; i<m_interfaces.size(); i++)
        delete m_interfaces[i];
    m_interfaces.clear();

    m_layers_z.clear();

    getParameterPool()->clear(); // non-trivially needed
}

MultiLayer* MultiLayer::clone() const
{
    return cloneGeneric( [](const Layer* p_layer) { return p_layer->clone(); } );
}

MultiLayer* MultiLayer::cloneSliced(bool use_average_layers) const
{
    (void)use_average_layers;
    return clone();
}

MultiLayer* MultiLayer::cloneInvertB() const
{
    return cloneGeneric( [](const Layer* p_layer) { return p_layer->cloneInvertB(); } );
}

//! Returns pointer to the top interface of the layer.
//! nInterfaces = nLayers-1, first layer in multilayer doesn't have interface.
const LayerInterface* MultiLayer::layerTopInterface(size_t i_layer) const
{
    return i_layer>0 ? m_interfaces[ check_interface_index(i_layer-1) ] : 0;
}

//! Returns pointer to the bottom interface of the layer.
const LayerInterface* MultiLayer::layerBottomInterface(size_t i_layer) const
{
    return i_layer<m_interfaces.size() ? m_interfaces[ check_interface_index(i_layer) ] : 0;
}

HomogeneousMaterial MultiLayer::layerMaterial(size_t i_layer) const
{
    return *layer(i_layer)->material();
}

void MultiLayer::setLayerMaterial(size_t i_layer, HomogeneousMaterial material)
{
    auto p_layer = m_layers[check_layer_index(i_layer)];
    p_layer->setMaterial(material);
}

void MultiLayer::addLayout(const ILayout & layout)
{
    ILayout *clone = layout.clone();
    m_layouts.push_back(clone);
    registerChild(clone);
}

//! Adds layer with top roughness

void MultiLayer::addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness)
{
    Layer* p_new_layer = layer.clone();
    if (numberOfLayers()) {
        // not the top layer
        const Layer* p_last_layer = m_layers.back();
        LayerInterface* interface(0);
        if (roughness.getSigma() != 0.0)
            interface = LayerInterface::createRoughInterface(p_last_layer, p_new_layer, roughness);
        else
            interface = LayerInterface::createSmoothInterface(p_last_layer, p_new_layer);
        addAndRegisterInterface(interface);
        m_layers_z.push_back(m_layers_z.back() - layer.thickness() );
    } else {
        // the top layer
        if (p_new_layer->thickness() != 0.0)
            throw std::runtime_error(
                "Invalid call to MultiLayer::addLayer(): the semi-infinite top layer "
                "must have a pro forma thickness of 0");
        m_layers_z.push_back(0.0);
    }
    addAndRegisterLayer(p_new_layer);
}

//! Adds layer with default (zero) roughness

void MultiLayer::addLayer(const Layer& layer)
{
    LayerRoughness zero_roughness;
    addLayerWithTopRoughness(layer, zero_roughness);
}


//! Fourier transform of the correlation function of roughnesses between the interfaces
//! j,k - indexes of layers in multilayer whose bottom interfaces we are considering
double MultiLayer::crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const
{
    if (m_crossCorrLength == 0)
        return 0.0;
    double z_j = layerBottomZ(j);
    double z_k = layerBottomZ(k);
    const LayerRoughness* rough_j = layerBottomInterface(j)->getRoughness();
    const LayerRoughness* rough_k = layerBottomInterface(k)->getRoughness();
    if (!rough_j || !rough_k)
        return 0.0;
    double sigma_j = rough_j->getSigma();
    double sigma_k = rough_k->getSigma();
    if (sigma_j == 0 || sigma_k == 0)
        return 0.0;
    double corr = 0.5*( (sigma_k/sigma_j)*rough_j->getSpectralFun(kvec) +
                        (sigma_j/sigma_k)*rough_k->getSpectralFun(kvec) ) *
        std::exp( -1*std::abs(z_j-z_k)/m_crossCorrLength );
    return corr;
}

int MultiLayer::indexOfLayer(const Layer* layer) const
{
    for (size_t i=0; i<numberOfLayers(); ++i)
        if (layer == m_layers[i])
            return i;
    return -1;
}

bool MultiLayer::containsMagneticMaterial() const
{
    for (const HomogeneousMaterial* mat: containedMaterials())
        if (mat->isMagneticMaterial())
            return true;
    return false;
}

bool MultiLayer::hasRoughness() const
{
    for (const LayerInterface* face: m_interfaces)
        if (face->getRoughness())
            return true;
    return false;
}

size_t MultiLayer::totalNofLayouts() const
{
    size_t ret = 0;
    for (const Layer* layer: m_layers)
        ret += layer->numberOfLayouts();
    return ret;
}

bool MultiLayer::containsParticles() const
{
    for (auto* p_layer: m_layers)
        if (p_layer->containsParticles())
            return true;
    return false;
}

std::vector<const INode*> MultiLayer::getChildren() const
{
    std::vector<const INode*> result;
    for(auto layer : m_layers) {
        result.push_back(layer);
        if(const LayerInterface *interface = layerBottomInterface(indexOfLayer(layer)))
            result.push_back(interface);
    }
    return result;
}

void MultiLayer::addAndRegisterLayer(Layer* child)
{
    m_layers.push_back(child);
    handleLayerThicknessRegistration();
    registerChild(child);
}

void MultiLayer::addAndRegisterInterface(LayerInterface* child)
{
    m_interfaces.push_back(child);
    registerChild(child);
}

void MultiLayer::handleLayerThicknessRegistration() const
{
    size_t n_layers = numberOfLayers();
    for (size_t i=0; i<numberOfLayers(); ++i) {
        if(i == 0 || i == n_layers-1) {
            m_layers[i]->registerThickness(false);
        } else {
            m_layers[i]->registerThickness(true);
        }
    }
}

size_t MultiLayer::check_layer_index(size_t i_layer) const
{
    if (i_layer >= m_layers.size())
        throw Exceptions::OutOfBoundsException("Layer index is out of bounds");
    return i_layer;
}

size_t MultiLayer::check_interface_index(size_t i_interface) const
{
    if (i_interface >= m_interfaces.size())
        throw Exceptions::OutOfBoundsException("Interface index is out of bounds");
    return i_interface;
}

MultiLayer* MultiLayer::cloneGeneric(const std::function<Layer*(const Layer*)>& layer_clone) const
{
    std::unique_ptr<MultiLayer> P_result(new MultiLayer());
    for (size_t i=0; i<numberOfLayers(); ++i)
    {
        auto p_interface = i>0 ? m_interfaces[i-1]
                               : nullptr;
        std::unique_ptr<Layer> P_layer(layer_clone(m_layers[i]));
        if (i>0 && p_interface->getRoughness())
            P_result->addLayerWithTopRoughness(*P_layer, *p_interface->getRoughness());
        else
            P_result->addLayer(*P_layer);
    }
    return P_result.release();
}

bool MultiLayer::requiresMatrixRTCoefficients() const
{
    for (auto layer: m_layers)
        if (!(layer->material()->isScalarMaterial()))
            return true;
    return false;
}

size_t MultiLayer::bottomZToLayerIndex(double z_value) const
{
    size_t n_layers = m_layers_z.size();
    if (n_layers < 2)
        return 0;
    if (z_value < m_layers_z[n_layers-2]) return m_layers_z.size()-1;
    auto top_limit = std::upper_bound(m_layers_z.rbegin()+1, m_layers_z.rend(), z_value);
    size_t nbin = static_cast<size_t>(m_layers_z.rend() - top_limit);
    return nbin;
}

size_t MultiLayer::topZToLayerIndex(double z_value) const
{
    size_t n_layers = m_layers_z.size();
    if (n_layers < 2)
        return 0;
    if (z_value < m_layers_z[n_layers-2]) return m_layers_z.size()-1;
    auto bottom_limit = std::lower_bound(m_layers_z.rbegin()+1, m_layers_z.rend(), z_value);
    size_t nbin = static_cast<size_t>(m_layers_z.rend() - bottom_limit);
    return nbin;
}

double MultiLayer::layerTopZ(size_t i_layer) const
{
    if (i_layer==0)
        return 0.0;
    return layerBottomZ(i_layer-1);
}

double MultiLayer::layerBottomZ(size_t i_layer) const
{
    if (numberOfLayers()<2)
        return 0;
    // Never use last entry in m_layers_z:
    if (i_layer==numberOfLayers()-1)
        --i_layer;
    return m_layers_z[ check_layer_index(i_layer) ];
}

double MultiLayer::layerThickness(size_t i_layer) const
{
    return m_layers[ check_layer_index(i_layer) ]->thickness();
}

void MultiLayer::setCrossCorrLength(double crossCorrLength)
{
    if (crossCorrLength<0.0)
        throw Exceptions::LogicErrorException("Attempt to set crossCorrLength to negative value");
    m_crossCorrLength = crossCorrLength;
}
