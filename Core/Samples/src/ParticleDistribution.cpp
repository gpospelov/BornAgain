// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleDistribution.cpp
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
#include "ParticleInfo.h"

#include <boost/scoped_ptr.hpp>

ParticleDistribution::ParticleDistribution(const IParticle &prototype,
                                           const ParameterDistribution &par_distr)
    : m_par_distribution(par_distr)
{
    setName("ParticleDistribution");
    mP_particle.reset(prototype.clone());
    registerChild(mP_particle.get());
}

ParticleDistribution::ParticleDistribution(const IParticle &prototype,
                                           const ParameterDistribution &par_distr,
                                           kvector_t position)
    : m_par_distribution(par_distr)
{
    setName("ParticleDistribution");
    mP_particle.reset(prototype.clone());
    mP_particle->setPosition(position);
    registerChild(mP_particle.get());
}

ParticleDistribution *ParticleDistribution::clone() const
{
    ParticleDistribution *p_result
        = new ParticleDistribution(*mP_particle, m_par_distribution);
    return p_result;
}

ParticleDistribution *ParticleDistribution::cloneInvertB() const
{
    throw Exceptions::NotImplementedException("ParticleDistribution::"
                                              "cloneInvertB: should never be called");
}

IFormFactor *ParticleDistribution::createTransformedFormFactor(complex_t, const IRotation *,
                                                               kvector_t) const
{
    throw Exceptions::NotImplementedException(
        "ParticleDistribution::"
        "createTransformedFormFactor: should never be called");
}

std::vector<ParticleInfo *> ParticleDistribution::generateParticleInfos(double abundance) const
{
    std::vector<ParticleInfo *> result;
    boost::scoped_ptr<ParameterPool> P_pool(createDistributedParameterPool() );
    std::string main_par_name = m_par_distribution.getMainParameterName();
    std::vector<ParameterPool::parameter_t> main_par_matches
        = P_pool->getMatchedParameters(main_par_name);
    if (main_par_matches.size() != 1) {
        throw Exceptions::RuntimeErrorException("ParticleDistribution::generateParticleInfos: "
                                                "main parameter name matches nothing or more than "
                                                "one parameter");
    }
    ParameterPool::parameter_t main_par = main_par_matches[0];
    double main_par_value = main_par.getValue();
    std::vector<ParameterSample> main_par_samples = m_par_distribution.generateSamples();
    std::vector<std::string> linked_par_names = m_par_distribution.getLinkedParameterNames();
    std::map<std::string, double> linked_par_ratio_map;
    for (size_t i = 0; i < linked_par_names.size(); ++i) {
        std::vector<ParameterPool::parameter_t> linked_par_matches
            = P_pool->getMatchedParameters(linked_par_names[i]);
        if (linked_par_matches.size() != 1) {
            throw Exceptions::RuntimeErrorException(
                "ParticleDistribution::generateParticleInfos: "
                "linked parameter name matches nothing or more than "
                "one parameter");
        }
        ParameterPool::parameter_t linked_par = linked_par_matches[0];
        double linked_par_value = linked_par.getValue();
        double linked_ratio = main_par_value == 0 ? 1.0 : linked_par_value / main_par_value;
        linked_par_ratio_map[linked_par_names[i]] = linked_ratio;
    }
    for (size_t i = 0; i < main_par_samples.size(); ++i) {
        ParameterSample main_sample = main_par_samples[i];
        double particle_abundance = abundance * main_sample.weight;
        ParticleInfo *p_particle_info = new ParticleInfo(*mP_particle);
        p_particle_info->setAbundance(particle_abundance);
        boost::scoped_ptr<ParameterPool> P_new_pool(
                    p_particle_info->getParticle()->createParameterTree() );
        int changed = P_new_pool->setMatchedParametersValue(main_par_name, main_sample.value);
        if (changed != 1) {
            throw Exceptions::RuntimeErrorException(
                "ParticleDistribution::generateParticleInfos: "
                "main parameter name matches nothing or more than "
                "one parameter");
        }
        for (std::map<std::string, double>::const_iterator it = linked_par_ratio_map.begin();
             it != linked_par_ratio_map.end(); ++it) {
            double new_linked_value = main_sample.value * it->second;
            changed = P_new_pool->setMatchedParametersValue(it->first, new_linked_value);
            if (changed != 1) {
                throw Exceptions::RuntimeErrorException(
                    "ParticleDistribution::generateParticleInfos: "
                    "linked parameter name matches nothing or more than "
                    "one parameter");
            }
        }
        if (mP_rotation.get()) p_particle_info->applyRotation(*mP_rotation);
        p_particle_info->applyTranslation(m_position);
        result.push_back(p_particle_info);
    }
    return result;
}
