// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particles/ParticleDistribution.cpp
//! @brief     Implements class ParticleDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleDistribution.h"
#include "BornAgainNamespace.h"
#include "ParameterSample.h"

ParticleDistribution::ParticleDistribution(const IParticle &prototype,
                                           const ParameterDistribution &par_distr)
    : m_par_distribution(par_distr)
{
    setName(BornAgain::ParticleDistributionType);
    mP_particle.reset(prototype.clone());
    registerChild(mP_particle.get());
}

ParticleDistribution *ParticleDistribution::clone() const
{
    ParticleDistribution *p_result
        = new ParticleDistribution(*mP_particle, m_par_distribution);
    p_result->setAbundance(m_abundance);
    return p_result;
}

ParticleDistribution *ParticleDistribution::cloneInvertB() const
{
    throw Exceptions::NotImplementedException("ParticleDistribution::"
                                              "cloneInvertB: should never be called");
}

void ParticleDistribution::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

void ParticleDistribution::setAmbientMaterial(const IMaterial &material)
{
    mP_particle->setAmbientMaterial(material);
}

const IMaterial *ParticleDistribution::getAmbientMaterial() const
{
    return mP_particle->getAmbientMaterial();
}

void ParticleDistribution::generateParticles(
        std::vector<const IParticle *> &particle_vector) const
{
    std::unique_ptr<ParameterPool> P_pool(createDistributedParameterPool());
    std::string main_par_name = m_par_distribution.getMainParameterName();
    std::vector<RealParameterWrapper> main_par_matches
        = P_pool->getMatchedParameters(main_par_name);
    if (main_par_matches.size() != 1) {
        throw Exceptions::RuntimeErrorException(
            "ParticleDistribution::generateParticles: "
            "main parameter name matches nothing or more than one parameter");
    }
    RealParameterWrapper main_par = main_par_matches[0];
    double main_par_value = main_par.getValue();
    std::vector<ParameterSample> main_par_samples = m_par_distribution.generateSamples();
    std::vector<std::string> linked_par_names = m_par_distribution.getLinkedParameterNames();
    std::map<std::string, double> linked_par_ratio_map;
    for (size_t i = 0; i < linked_par_names.size(); ++i) {
        std::vector<RealParameterWrapper> linked_par_matches
            = P_pool->getMatchedParameters(linked_par_names[i]);
        if (linked_par_matches.size() != 1) {
            throw Exceptions::RuntimeErrorException(
                "ParticleDistribution::generateParticles: "
                "linked parameter name matches nothing or more than one parameter");
        }
        RealParameterWrapper linked_par = linked_par_matches[0];
        double linked_par_value = linked_par.getValue();
        double linked_ratio = main_par_value == 0 ? 1.0 : linked_par_value / main_par_value;
        linked_par_ratio_map[linked_par_names[i]] = linked_ratio;
    }
    for (size_t i = 0; i < main_par_samples.size(); ++i) {
        ParameterSample main_sample = main_par_samples[i];
        double particle_abundance = getAbundance() * main_sample.weight;
        IParticle *p_particle_clone = mP_particle->clone();
        std::unique_ptr<ParameterPool> P_new_pool(p_particle_clone->createParameterTree());
        int changed = P_new_pool->setMatchedParametersValue(main_par_name, main_sample.value);
        if (changed != 1) {
            throw Exceptions::RuntimeErrorException(
                "ParticleDistribution::generateParticles: "
                "main parameter name matches nothing or more than one parameter");
        }
        for (std::map<std::string, double>::const_iterator it = linked_par_ratio_map.begin();
             it != linked_par_ratio_map.end(); ++it) {
            double new_linked_value = main_sample.value * it->second;
            changed = P_new_pool->setMatchedParametersValue(it->first, new_linked_value);
            if (changed != 1) {
                throw Exceptions::RuntimeErrorException(
                    "ParticleDistribution::generateParticles: "
                    "linked parameter name matches nothing or more than one parameter");
            }
        }
        p_particle_clone->setAbundance(particle_abundance);
        particle_vector.push_back(p_particle_clone);
    }
}

ParameterDistribution ParticleDistribution::getParameterDistribution() const
{
    return m_par_distribution;
}

ParameterPool *ParticleDistribution::createDistributedParameterPool() const
{
    return mP_particle->createParameterTree();
}

const IParticle *ParticleDistribution::getParticle() const
{
    return mP_particle.get();
}
