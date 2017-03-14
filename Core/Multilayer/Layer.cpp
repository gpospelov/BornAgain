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

Layer::Layer(HomogeneousMaterial material, double thickness)
    : m_material(std::move(material))
    , m_thickness(thickness)
{
    setName(BornAgain::LayerType);
    registerThickness();
}

Layer::Layer(const Layer& other)
    : m_material(other.m_material)
{
    setName(other.getName());
    m_thickness = other.m_thickness;
    for (size_t i=0; i<other.numberOfLayouts();++i)
        addLayout(*other.layout(i));
    registerThickness();
}

Layer::~Layer()
{}

Layer* Layer::cloneInvertB() const
{
    Layer* p_clone = new Layer(m_material.inverted(), m_thickness);
    return p_clone;
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw Exceptions::DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
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
