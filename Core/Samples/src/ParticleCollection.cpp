// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleCollection.cpp
//! @brief     Implements class ParticleCollection.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCollection.h"
#include "ParticleInfo.h"


ParticleCollection::ParticleCollection(const IParticle &prototype,
                                       const ParameterDistribution &par_distr)
    : m_par_distribution(par_distr)
{
    mP_particle.reset(prototype.clone());
    setName("ParticleCollection");
}

ParticleCollection *ParticleCollection::clone() const
{
    ParticleCollection *p_result = new ParticleCollection(*mP_particle,
                                                          m_par_distribution);
    return p_result;
}

ParticleCollection *ParticleCollection::cloneInvertB() const
{
    throw Exceptions::NotImplementedException("ParticleCollection::"
        "cloneInvertB: should never be called");
}

IFormFactor *ParticleCollection::createFormFactor(
        complex_t wavevector_scattering_factor) const {
    (void)wavevector_scattering_factor;
    throw Exceptions::NotImplementedException("ParticleCollection::"
        "createFormFactor: should never be called");
}

const IFormFactor *ParticleCollection::getSimpleFormFactor() const {
    throw Exceptions::NotImplementedException("ParticleCollection::"
        "getSimpleFormFactor: should never be called");
}

std::vector<ParticleInfo *>
ParticleCollection::generateParticleInfos(kvector_t position,
                                          double abundance) const
{
    std::vector<ParticleInfo *> result;
    ParameterPool *pool = mP_particle->createParameterTree();
    std::string main_par_name =
            m_par_distribution.getMainParameterName();
    ParameterPool::parameter_t main_par = pool->getParameter(main_par_name);
    double main_par_value = main_par.getValue();
    std::vector<ParameterSample> main_par_samples =
            m_par_distribution.generateSamples();
    std::vector<std::string> linked_par_names =
            m_par_distribution.getLinkedParameterNames();
    std::map<std::string, double> linked_par_ratio_map;
    for (size_t i=0; i<linked_par_names.size(); ++i) {
        ParameterPool::parameter_t linked_par =
                pool->getParameter(linked_par_names[i]);
        double linked_par_value = linked_par.getValue();
        double linked_ratio = main_par_value==0 ? 1.0
                              : linked_par_value/main_par_value;
        linked_par_ratio_map[linked_par_names[i]] = linked_ratio;
    }
    for (size_t i=0; i<main_par_samples.size(); ++i) {
        boost::scoped_ptr<IParticle> P_prototype(mP_particle->clone());
        ParameterPool *new_pool = P_prototype->createParameterTree();
        ParameterSample main_sample = main_par_samples[i];
        new_pool->setParameterValue(main_par_name, main_sample.value);
        for (std::map<std::string, double>::const_iterator it =
             linked_par_ratio_map.begin(); it != linked_par_ratio_map.end();
             ++it) {
            double new_linked_value = main_sample.value * it->second;
            new_pool->setParameterValue(it->first, new_linked_value);
        }
        double particle_abundance = abundance*main_sample.weight;
        ParticleInfo *p_particle_info = new ParticleInfo(*P_prototype, position,
                                                         particle_abundance);
        result.push_back(p_particle_info);
    }
    return result;
}

void ParticleCollection::applyTransformationToSubParticles(
        const Geometry::Transform3D& transform)
{
    mP_particle->applyTransformation(transform);
    return;
}


