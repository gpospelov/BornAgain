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
#include <iomanip>


Layer::Layer()
    : mp_material(0)
    , mp_decoration(0)
    , m_thickness(0)
{
    setName("Layer");
    init_parameters();
}


Layer::Layer(const IMaterial* material, double thickness)
    : mp_decoration(0)
    , m_thickness(thickness)
{
    setName("Layer");
    setMaterial(material);
    init_parameters();
}


Layer::Layer(const Layer& other) : ICompositeSample()
{
    mp_material = other.mp_material;
    mp_decoration = 0;
    if(other.getDecoration()) mp_decoration = other.getDecoration()->clone();
    m_thickness = other.m_thickness;
    setName(other.getName());
    init_parameters();
}


Layer::~Layer()
{
    delete mp_decoration;
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
void Layer::setMaterial(const IMaterial* material)
{
    if ( !material )
        throw NullPointerException("The material doesn't exist");
    mp_material = material;
}


void Layer::setMaterial(const IMaterial* material, double thickness)
{
    setMaterial(material);
    setThickness(thickness);
}


//! Prints description.
void Layer::print(std::ostream& ostr) const
{
    ICompositeSample::print(ostr);
    ostr << "-->Layer{" <<  *getMaterial() << "}";
}


LayerDWBASimulation *Layer::createDWBASimulation() const
{
    if(mp_decoration) {
        return new LayerDecoratorDWBASimulation(this);
    }
    return 0;
}


DiffuseDWBASimulation* Layer::createDiffuseDWBASimulation() const
{
    DiffuseDWBASimulation *p_sim = new DiffuseDWBASimulation;
    size_t nbr_particles = mp_decoration->getNumberOfParticles();
    double particle_density = mp_decoration->getTotalParticleSurfaceDensity();
    for (size_t i=0; i<nbr_particles; ++i) {
        const ParticleInfo *p_info = mp_decoration->getParticleInfo(i);
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
            break; // TODO: remove this break (this necessitates the creation of a phi-averaged mesocrystal class generating only one nanoparticle for diffuse calculations)
        }
    }
    if (p_sim->getSize()>0) {
        p_sim->setRefractiveIndex(getRefractiveIndex());
        return p_sim;
    }
    delete p_sim;
    return 0;
}
