// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Layer.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "ILayout.h"
#include "ParameterPool.h"
#include "RealParameter.h"

#include <set>

Layer::Layer(HomogeneousMaterial material, double thickness)
    : m_material(std::move(material))
    , m_thickness(thickness)
{
    setName(BornAgain::LayerType);
    registerThickness();
}

Layer::~Layer()
{}

Layer* Layer::cloneInvertB() const
{
    Layer* p_clone = new Layer(m_material.inverted(), m_thickness);
    return p_clone;
}

SafePointerVector<Layer> Layer::cloneSliced(ZLimits limits, Layer::ELayerType layer_type) const
{
    SafePointerVector<Layer> result;
    // no slicing when there are no limits or #slices is zero
    if (!limits.isFinite() || m_n_slices==0 || layer_type==ONLYLAYER) {
        result.push_back(clone());
        return result;
    }
    double bottom = limits.lowerLimit().m_value;
    double top = limits.upperLimit().m_value;
    double slice_thickness = (top-bottom)/m_n_slices;
    // empty top layer
    double empty_top_thickness = (layer_type==TOPLAYER) ? 0 : -top;
    if (empty_top_thickness>0 || layer_type==TOPLAYER)
    {
        result.push_back(new Layer(m_material, empty_top_thickness));
    }
    // slices containing particles
    double offset = -top;
    for (size_t i=0; i<m_n_slices; ++i)
    {
        if (i==0)
        {
            Layer* p_layer = cloneWithOffset(offset);
            p_layer->setThickness(slice_thickness);
            result.push_back(p_layer);
        }
        else
        {
            Layer* p_layer = emptyClone();
            p_layer->setThickness(slice_thickness);
            result.push_back(p_layer);
        }
    }
    // empty bottom layer
    double layer_thickness = (layer_type==INTERMEDIATELAYER) ? thickness() : 0;
    double empty_bottom_thickness = (layer_type==BOTTOMLAYER) ? 0 : bottom + layer_thickness;
    if (empty_bottom_thickness>0 || layer_type==BOTTOMLAYER)
    {
        result.push_back(new Layer(m_material, empty_bottom_thickness));
    }
    return result;
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw Exceptions::DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
}

void Layer::setMaterial(HomogeneousMaterial material)
{
    m_material = std::move(material);
}

complex_t Layer::refractiveIndex() const
{
    return m_material.refractiveIndex();
}

//TODO: remove this in favor of the HomogeneousMaterial methods (or rename)
complex_t Layer::refractiveIndex2() const
{
    return refractiveIndex()*refractiveIndex();
}

void Layer::addLayout(const ILayout& layout)
{
    ILayout* clone = layout.clone();
    m_layouts.push_back(clone);
    registerChild(clone);
}

const ILayout* Layer::layout(size_t i) const
{
    if (i>=m_layouts.size())
        return nullptr;
    return m_layouts[i];
}

bool Layer::containsParticles() const
{
    for (size_t i=0; i<numberOfLayouts(); ++i)
        if (layout(i)->numberOfParticles()>0)
            return true;
    return false;
}

double Layer::topZParticles() const
{
    if (!containsParticles())
        throw std::runtime_error("Layer::topZParticles(): no particles in this layer.");
    std::set<double> topValues;
    for (size_t i=0; i<numberOfLayouts(); ++i)
        if (layout(i)->numberOfParticles())
            topValues.insert(layout(i)->topZParticles());
    return *topValues.rbegin();
}

double Layer::bottomZParticles() const
{
    if (!containsParticles())
        throw std::runtime_error("Layer::bottomZParticles(): no particles in this layer.");
    std::set<double> bottomValues;
    for (size_t i=0; i<numberOfLayouts(); ++i)
        if (layout(i)->numberOfParticles())
            bottomValues.insert(layout(i)->bottomZParticles());
    return *bottomValues.begin();
}

std::vector<const INode*> Layer::getChildren() const
{
    std::vector<const INode*> result;
    for(auto layout : m_layouts)
        result.push_back(layout);
    return result;
}

void Layer::registerThickness(bool make_registered)
{
    if(make_registered) {
        if(!getParameter(BornAgain::Thickness))
            registerParameter(BornAgain::Thickness, &m_thickness).setUnit("nm").setNonnegative();
    } else {
        removeParameter(BornAgain::Thickness);
    }
}

Layer::Layer(const Layer& other)
    : m_material(other.m_material)
{
    setName(other.getName());
    m_thickness = other.m_thickness;
    m_n_slices = other.m_n_slices;
    for (size_t i=0; i<other.numberOfLayouts();++i)
        addLayout(*other.layout(i));
    registerThickness();
}

Layer* Layer::emptyClone() const
{
    Layer* p_result = new Layer(m_material, m_thickness);
    p_result->setName(getName());
    return p_result;
}

Layer* Layer::cloneWithOffset(double offset) const
{
    Layer* p_result = emptyClone();
    for (size_t i=0; i<numberOfLayouts();++i)
    {
        ILayout* p_layout = layout(i)->cloneWithOffset(offset);
        p_result->m_layouts.push_back(p_layout);
        p_result->registerChild(p_layout);
    }
    return p_result;
}
