// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleBuilder.cpp
//! @brief     Implements class ParticleBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleBuilder.h"
#include "ParticleLayout.h"
#include "Numeric.h"

#include <numeric>
#include <algorithm>

ParticleBuilder::ParticleBuilder()
    : mp_prototype(0)
    , mp_distribution(0)
    , m_nbr_samples(0)
    , m_sigma_factor(0.0)
    , m_scale(0)
{
}

ParticleBuilder::~ParticleBuilder()
{
    delete mp_prototype;
    delete mp_distribution;
}

//! Sets prototype for particle production

void ParticleBuilder::setPrototype(const Particle &particle, std::string name,
    const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor,
    double scale)
{
    delete mp_prototype;
    mp_prototype = particle.clone();
    m_parameter_name = name;
    delete mp_distribution;
    mp_distribution = distribution.clone();
    m_nbr_samples = nbr_samples;
    m_sigma_factor = sigma_factor;
    m_scale = scale;
}

//! plant particles in given decoration

void ParticleBuilder::plantParticles(ParticleLayout& layout)
{
    if( !mp_prototype ) throw NullPointerException(
        "ParticleBuilder::plantParticle() -> Error. No prototype is defined");

    if( !mp_distribution ) throw NullPointerException(
        "ParticleBuilder::plantParticle() -> Error. No distribution is defined");

    ParameterPool *pool = mp_prototype->createParameterTree();

    // generate parameter samples
    std::vector<ParameterSample> samples =
            mp_distribution->generateSamples(m_nbr_samples, m_sigma_factor);

    // find maximum weight
    double max_weight = 0.0;
    for(std::vector<ParameterSample>::const_iterator it = samples.begin();
        it != samples.end(); ++it) {
        max_weight = std::max(max_weight, it->weight);
    }


    // loop over sampled parameter values
    for(std::vector<ParameterSample>::const_iterator it = samples.begin();
        it != samples.end(); ++it) {

        double weight = it->weight;
        double value = it->value;

        // changing value of the particle's parameter and making clone
        pool->setParameterValue(m_parameter_name, value);
        Particle *particle = mp_prototype->clone();

        if(weight/max_weight > Numeric::probthreshold)  { // isgisaxs way
            layout.addParticle(*particle, 0.0, weight*m_scale);
        }

        delete particle;
    }

    delete pool;
}


