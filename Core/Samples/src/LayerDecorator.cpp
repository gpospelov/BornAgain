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

void LayerDecorator::print(std::ostream& ostr) const
{
    Layer::print(ostr);
    ostr << "-->LayerDecorator{" << *mp_decoration << "}";
}
