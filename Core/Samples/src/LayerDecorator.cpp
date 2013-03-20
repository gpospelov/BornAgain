// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/LayerDecorator.cpp
//! @brief     Implements class LayerDecorator.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "LayerDecorator.h"

LayerDecorator::LayerDecorator(const Layer &layer,
        const IDecoration &decoration)
: mp_decorated_layer(layer.clone())
, mp_decoration(decoration.clone())
{
    setName("LayerDecorator");
    registerChild(mp_decorated_layer);
    registerChild(mp_decoration);
    init_parameters();
}

LayerDecorator* LayerDecorator::clone() const
{
    return new LayerDecorator(*this);
}

LayerDecorator::~LayerDecorator()
{
    delete mp_decorated_layer;
    delete mp_decoration;
}

// LayerDecorator is derived from Layer and it has to clean all parameters created by Layer
void LayerDecorator::init_parameters()
{
    getParameterPool()->clear();
}

DiffuseDWBASimulation* LayerDecorator::createDiffuseDWBASimulation() const
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
                p_diff_info->setNumberPerMeso(particle_density*p_info->getAbundance()
                        *p_diff_info->getNumberPerMeso());
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

LayerDecorator::LayerDecorator(const LayerDecorator& other)
: Layer(other)
{
    mp_decorated_layer = other.getDecoratedLayer()->clone();
    mp_decoration = other.getDecoration()->clone();

    setName("LayerDecorator");
    registerChild(mp_decorated_layer);
    registerChild(mp_decoration);
    init_parameters();
}

void LayerDecorator::print(std::ostream &ostr) const
{
    ICompositeSample::print(ostr);
}
