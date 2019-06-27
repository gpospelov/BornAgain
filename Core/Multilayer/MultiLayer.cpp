// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayer.cpp
//! @brief     Implements class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultiLayer.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "ILayout.h"
#include "Layer.h"
#include "LayerFillLimits.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "MaterialUtils.h"
#include "MultiLayerUtils.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include <iomanip>

MultiLayer::MultiLayer() : m_crossCorrLength(0)
{
    setName(BornAgain::MultiLayerType);
    init_parameters();
}

MultiLayer::~MultiLayer()
{}

void MultiLayer::init_parameters()
{
    parameterPool()->clear(); // non-trivially needed
    registerParameter(BornAgain::CrossCorrelationLength, &m_crossCorrLength).
        setUnit(BornAgain::UnitsNm).setNonnegative();
    registerVector(BornAgain::ExternalField, &m_ext_field, BornAgain::UnitsNone);
}

MultiLayer* MultiLayer::clone() const
{
    std::unique_ptr<MultiLayer> P_result(new MultiLayer());
    P_result->setCrossCorrLength(crossCorrLength());
    P_result->setExternalField(externalField());
    for (size_t i=0; i<numberOfLayers(); ++i)
    {
        auto p_interface = i>0 ? m_interfaces[i-1]
                               : nullptr;
        std::unique_ptr<Layer> P_layer(m_layers[i]->clone());
        if (i>0 && p_interface->getRoughness())
            P_result->addLayerWithTopRoughness(*P_layer, *p_interface->getRoughness());
        else
            P_result->addLayer(*P_layer);
    }
    return P_result.release();
}

const LayerRoughness* MultiLayer::layerTopRoughness(size_t i_layer) const
{
    if (i_layer==0) return nullptr;
    return m_interfaces[check_interface_index(i_layer-1)]->getRoughness();
}



//! Returns pointer to the top interface of the layer.
//! nInterfaces = nLayers-1, first layer in multilayer doesn't have interface.
const LayerInterface* MultiLayer::layerTopInterface(size_t i_layer) const
{
    return i_layer>0 ? m_interfaces[ check_interface_index(i_layer-1) ] : nullptr;
}

//! Returns pointer to the bottom interface of the layer.
const LayerInterface* MultiLayer::layerBottomInterface(size_t i_layer) const
{
    return i_layer<m_interfaces.size() ? m_interfaces[ check_interface_index(i_layer) ] : nullptr;
}

//! Adds layer with top roughness
void MultiLayer::addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness)
{
    Layer* p_new_layer = layer.clone();
    if (numberOfLayers()) {
        // not the top layer
        const Layer* p_last_layer = m_layers.back();
        LayerInterface* interface(nullptr);
        if (roughness.getSigma() != 0.0)
            interface = LayerInterface::createRoughInterface(p_last_layer, p_new_layer, roughness);
        else
            interface = LayerInterface::createSmoothInterface(p_last_layer, p_new_layer);
        addAndRegisterInterface(interface);
    } else {
        // the top layer
        if (p_new_layer->thickness() != 0.0)
            throw std::runtime_error(
                "Invalid call to MultiLayer::addLayer(): the semi-infinite top layer "
                "must have a pro forma thickness of 0");
    }
    addAndRegisterLayer(p_new_layer);
}

//! Adds layer with default (zero) roughness

void MultiLayer::addLayer(const Layer& layer)
{
    LayerRoughness zero_roughness;
    addLayerWithTopRoughness(layer, zero_roughness);
}


size_t MultiLayer::indexOfLayer(const Layer* p_layer) const
{
    for (size_t i=0; i<numberOfLayers(); ++i)
        if (p_layer == m_layers[i])
            return i;
    throw std::out_of_range("MultiLayer::indexOfLayer: layer not found");
}

bool MultiLayer::containsMagneticMaterial() const
{
    for (const Material* mat: containedMaterials())
        if (mat->isMagneticMaterial())
            return true;
    return false;
}

bool MultiLayer::containsCompatibleMaterials() const
{
    return MaterialUtils::checkMaterialTypes(containedMaterials())
           != MATERIAL_TYPES::InvalidMaterialType;
}

void MultiLayer::initBFields()
{
    if (numberOfLayers()==0)
        return;
    double m_z0 = m_layers[0]->material()->magnetization().z();
    double b_z = Layer::Magnetic_Permeability*(m_ext_field.z()+m_z0);
    for (size_t i=0; i<numberOfLayers(); ++i) {
        m_layers[i]->initBField(m_ext_field, b_z);
    }
}

bool MultiLayer::hasRoughness() const
{
    for (auto p_interface: m_interfaces)
        if (p_interface->getRoughness())
            return true;
    return false;
}

size_t MultiLayer::totalNofLayouts() const
{
    size_t ret = 0;
    for (auto p_layer: m_layers)
        ret += p_layer->numberOfLayouts();
    return ret;
}

std::vector<const INode*> MultiLayer::getChildren() const
{
    std::vector<const INode*> result;
    for(auto p_layer : m_layers) {
        result.push_back(p_layer);
        if(const LayerInterface* p_interface = layerBottomInterface(indexOfLayer(p_layer)))
            result.push_back(p_interface);
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

void MultiLayer::handleLayerThicknessRegistration()
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

void MultiLayer::setExternalField(kvector_t ext_field)
{
    m_ext_field = ext_field;
}
