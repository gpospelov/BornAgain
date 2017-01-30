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
#include "IMaterial.h"
#include "ParameterPool.h"
#include "RealParameter.h"

Layer::Layer(const IMaterial& material, double thickness)
    : mp_material(nullptr), m_thickness(thickness)
{
    setMaterial(material);
    initialize();
}

Layer::Layer(const Layer& other)
    : ISample(), mp_material(nullptr)
{
    m_thickness = other.m_thickness;
    if (other.mp_material)
        mp_material = other.mp_material->clone();
    for (size_t i=0; i<other.getNumberOfLayouts();++i)
        addLayout(*other.getLayout(i));
    initialize();
}

Layer::~Layer()
{
    delete mp_material;
}

Layer* Layer::cloneInvertB() const
{
    Layer* p_clone = new Layer(*mp_material->cloneInverted(), m_thickness);
    p_clone->init_parameters();
    return p_clone;
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw Exceptions::DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
}

//! Sets _material_ of the layer.
void Layer::setMaterial(const IMaterial& material)
{
    delete mp_material;
    mp_material = material.clone();
}

complex_t Layer::getRefractiveIndex() const
{
    return mp_material ? mp_material->getRefractiveIndex() : 1.0;
}

//TODO: remove this in favor of the IMaterial methods (or rename)
complex_t Layer::getRefractiveIndex2() const
{
    return getRefractiveIndex()*getRefractiveIndex();
}

void Layer::addLayout(const ILayout& layout)
{
    ILayout* clone = layout.clone();
    m_layouts.push_back(clone);
    registerChild(clone);
}

const ILayout* Layer::getLayout(size_t i) const
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

void Layer::init_parameters()
{
    getParameterPool()->clear(); // non-trivially needed
    registerParameter(BornAgain::Thickness, &m_thickness).setUnit("nm").setNonnegative();
}

void Layer::initialize()
{
    setName(BornAgain::LayerType);
    init_parameters();
}
