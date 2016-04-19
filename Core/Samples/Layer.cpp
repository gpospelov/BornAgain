// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/Layer.cpp
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
#include "DecoratedLayerDWBASimulation.h"
#include "MultiLayer.h"

#include <iomanip>

using namespace BornAgain;

Layer::Layer() : m_thickness(0), mp_material(0)
{
    initialize();
}

Layer::Layer(const IMaterial &material, double thickness) : m_thickness(thickness), mp_material(0)
{
    setMaterial(material);
    initialize();
}

Layer::Layer(const Layer& other) : ICompositeSample()
{
    m_thickness = other.m_thickness;
    mp_material = 0;
    if(other.mp_material) mp_material = other.mp_material->clone();
    for (size_t i=0; i<other.getNumberOfLayouts();++i) {
        addLayoutPtr(other.getLayout(i)->clone());
    }
    setNumberOfLayers(other.getNumberOfLayers());
    initialize();
}

Layer::~Layer()
{
    delete mp_material;
}

Layer *Layer::clone() const
{
    return new Layer(*this);
}

Layer* Layer::cloneInvertB() const
{
    Layer *p_clone = new Layer();
    p_clone->mp_material = Materials::createInvertedMaterial(this->mp_material);
    for (size_t i=0; i<getNumberOfLayouts(); ++i) {
        p_clone->addLayoutPtr(getLayout(i)->cloneInvertB());
    }
    p_clone->m_thickness = this->m_thickness;
    p_clone->setNumberOfLayers(getNumberOfLayers());
    p_clone->init_parameters();
    return p_clone;
}

void Layer::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
}

double Layer::getThickness() const
{
    return m_thickness;
}

//! Sets _material_ of the layer.
void Layer::setMaterial(const IMaterial &material)
{
    delete mp_material;
    mp_material = material.clone();
}

void Layer::setMaterialAndThickness(const IMaterial &material, double thickness)
{
    setMaterial(material);
    setThickness(thickness);
}

const IMaterial *Layer::getMaterial() const
{
    return mp_material;
}

complex_t Layer::getRefractiveIndex() const
{
    return (mp_material ? mp_material->getRefractiveIndex()
                        : complex_t(1.0,0.0));
}

complex_t Layer::getRefractiveIndex2() const
{
    return getRefractiveIndex()*getRefractiveIndex();
}

void Layer::addLayout(const ILayout &decoration)
{
    addLayoutPtr(decoration.clone());
}

const ILayout *Layer::getLayout(size_t i) const
{
    if (i>=m_layouts.size()) {
        return 0;
    }
    return m_layouts[i];
}

bool Layer::hasDWBASimulation() const
{
    return (m_layouts.size()>0);
}

LayerDWBASimulation *Layer::createLayoutSimulation(size_t layout_index) const
{
    if(getNumberOfLayouts()==0 || layout_index>=getNumberOfLayouts()) {
        return 0;
    }
    return new DecoratedLayerDWBASimulation(this, layout_index);
}

double Layer::getTotalParticleSurfaceDensity(size_t layout_index) const
{
    if (getNumberOfLayouts()==0 || layout_index>=getNumberOfLayouts()) {
        return 0.0;
    }
    return getLayout(layout_index)->getTotalParticleSurfaceDensity();
}

double Layer::getTotalAbundance() const
{
    double total_abundance = 0.0;
    for (size_t i=0; i<getNumberOfLayouts(); ++i) {
        total_abundance += getLayout(i)->getTotalAbundance();
    }
    return total_abundance;
}

void Layer::setNumberOfLayers(size_t n_layers)
{
    mn_layers = n_layers;
}

size_t Layer::getNumberOfLayers() const
{
    return mn_layers;
}

void Layer::init_parameters()
{
    clearParameterPool();
    registerParameter(Thickness, &m_thickness);
}

//! Prints description.
void Layer::print(std::ostream& ostr) const
{
    ICompositeSample::print(ostr);
    ostr << "-->Layer{" <<  *getMaterial() << "}";
}

void Layer::addLayoutPtr(ILayout *layout)
{
    if( !layout ) return;

    m_layouts.push_back(layout);
    registerChild(layout);
}

void Layer::initialize()
{
    setName(LayerType);
    init_parameters();
}
