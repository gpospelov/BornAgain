// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Layer.h"
#include "Exceptions.h"
#include "DecoratedLayerDWBASimulation.h"
#include "MultiLayer.h"

#include <iomanip>


Layer::Layer()
    : m_thickness(0)
    , mp_material(0)
    , mp_layout(0)
{
    setName("Layer");
    init_parameters();
}

Layer::Layer(const IMaterial &material, double thickness)
    : m_thickness(thickness)
    , mp_material(0)
    , mp_layout(0)
{
    setName("Layer");
    setMaterial(material);
    init_parameters();
}

Layer::Layer(const Layer& other) : ICompositeSample()
{
    mp_material = 0;
    if(other.mp_material) mp_material = other.mp_material->clone();
    mp_layout = 0;
    if(other.getLayout()) {
        setLayoutPtr(other.getLayout()->clone());
    }
    m_thickness = other.m_thickness;
    setName(other.getName());
    setNumberOfLayers(other.getNumberOfLayers());
    init_parameters();
}

Layer::~Layer()
{
    delete mp_material;
    delete mp_layout;
}

Layer* Layer::cloneInvertB() const
{
    Layer *p_clone = new Layer();
    p_clone->mp_material = Materials::createInvertedMaterial(this->mp_material);
    p_clone->mp_layout = 0;
    if(this->getLayout()) {
        p_clone->setLayoutPtr(this->getLayout()->cloneInvertB());
    }
    p_clone->m_thickness = this->m_thickness;
    std::string clone_name = this->getName() + "_inv";
    p_clone->setName(clone_name);
    p_clone->setNumberOfLayers(getNumberOfLayers());
    p_clone->init_parameters();
    return p_clone;
}

void Layer::init_parameters()
{
    clearParameterPool();
    registerParameter("thickness", &m_thickness);
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
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

void Layer::setLayoutPtr(ILayout *layout)
{
    if( !layout ) return;

    if(mp_layout) {
        deregisterChild(mp_layout);
        delete mp_layout;
    }
    mp_layout = layout;
    registerChild(mp_layout);
}

void Layer::setLayout(const ILayout &decoration)
{
    setLayoutPtr(decoration.clone());
}

//! Prints description.
void Layer::print(std::ostream& ostr) const
{
    ICompositeSample::print(ostr);
    ostr << "-->Layer{" <<  *getMaterial() << "}";
}

LayerDWBASimulation *Layer::createDWBASimulation() const
{
    if(mp_layout) {
        return new DecoratedLayerDWBASimulation(this);
    }
    return 0;
}

DiffuseDWBASimulation* Layer::createDiffuseDWBASimulation() const
{
    if(!mp_layout) return 0;

    DiffuseDWBASimulation *p_sim = new DiffuseDWBASimulation;
    size_t nbr_particles = mp_layout->getNumberOfParticles();
    double particle_density = mp_layout->getTotalParticleSurfaceDensity();
    const IMaterial *p_layer_material = getMaterial();
    for (size_t i=0; i<nbr_particles; ++i) {
        const ParticleInfo *p_info = mp_layout->getParticleInfo(i);
        std::vector<DiffuseParticleInfo *> *p_diffuse_nps =
                p_info->getParticle()->createDiffuseParticleInfo(*p_info);
        if (p_diffuse_nps) {
            for (size_t j=0; j<p_diffuse_nps->size(); ++j) {
                DiffuseParticleInfo *p_diff_info = (*p_diffuse_nps)[j];
                p_diff_info->setNumberPerMeso(
                    particle_density * p_info->getAbundance() *
                    p_diff_info->getNumberPerMeso());
                p_sim->addParticleInfo((*p_diffuse_nps)[j]);
            }
            delete p_diffuse_nps;
            break; // TODO: remove this break (this necessitates the creation
                   // of a phi-averaged mesocrystal class generating only one
                   // nanoparticle for diffuse calculations)
        }
    }
    if (p_sim->getSize()>0) {
        p_sim->setMaterial(p_layer_material);
        return p_sim;
    }
    delete p_sim;
    return 0;
}

