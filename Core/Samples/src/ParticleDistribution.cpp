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
    registerParameter("position_x", &m_position[0]);
    registerParameter("position_y", &m_position[1]);
    registerParameter("position_z", &m_position[2]);
    checkParticleType(prototype);
    mP_particle.reset(prototype.clone());
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

std::vector<std::pair<const IParticle *, double> >
ParticleDistribution::generateParticleInfos(double abundance) const
{
    std::vector<std::pair<const IParticle *, double> > result;
    boost::scoped_ptr<ParameterPool> P_pool(createDistributedParameterPool());
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
        IParticle *p_particle_clone = mP_particle->clone();
        std::pair<const IParticle *, double> particle_abundance_pair(p_particle_clone,
                                                                     particle_abundance);
        boost::scoped_ptr<ParameterPool> P_new_pool(p_particle_clone->createParameterTree());
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
        result.push_back(particle_abundance_pair);
    }
    return result;
}

void ParticleDistribution::checkParticleType(const IParticle &p_particle)
{
    const ParticleDistribution *p_distr = dynamic_cast<const ParticleDistribution*>(&p_particle);
    if (p_distr) {
        throw Exceptions::ClassInitializationException("ParticleDistribution::checkParticleType: "
                                                       "cannot add ParticleDistribution!");
    }
}
