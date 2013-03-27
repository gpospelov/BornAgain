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
#include "ParticleDecoration.h"
#include "Numeric.h"
#include "StochasticSampledParameter.h"

#include <numeric>
#include <algorithm>

ParticleBuilder::ParticleBuilder() :
    m_prototype(0), m_parameter(0), m_scale(0)
{
}

ParticleBuilder::~ParticleBuilder()
{
    delete m_prototype;
    delete m_parameter;
}

//! Sets prototype for particle production

void ParticleBuilder::setPrototype(const Particle& particle, std::string name, const StochasticParameter<double>& param, double scale)
{
    delete m_prototype;
    m_prototype = particle.clone();
    m_parameter_name = name;
    delete m_parameter;
    m_parameter = param.clone();
    m_scale = scale;
}

//! plant particles in given decoration

void ParticleBuilder::plantParticles(ParticleDecoration& decor)
{
    if( !m_prototype ) throw NullPointerException("ParticleBuilder::plantParticle() -> Error. No prototype is defined");

    if( !m_parameter ) throw NullPointerException("ParticleBuilder::plantParticle() -> Error. No parameter is defined");

    ParameterPool *pool = m_prototype->createParameterTree();

    StochasticSampledParameter *sampled_parameter = dynamic_cast<StochasticSampledParameter *>(m_parameter);
    if( !sampled_parameter) {
        throw LogicErrorException("ParticleBuilder::plantParticle() -> Error. Not supported parameter type");
    }

    // calculating sum of all weights, and maximum value
    std::vector<double> weights;
    for(size_t i=0; i<sampled_parameter->getNbins(); ++i) weights.push_back(sampled_parameter->probabilityBinDensity(i));
    double maximum_value = *std::max_element(weights.begin(), weights.end());
    double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);

    // loop over sampled parameter values
    for(size_t i=0; i<sampled_parameter->getNbins(); ++i) {

        double weight = sampled_parameter->probabilityBinDensity(i);
        double value = sampled_parameter->getBinValue(i);

        // changing value of the particle's parameter and making clone
        pool->setParameterValue(m_parameter_name, value);
        Particle *particle = m_prototype->clone();

        if(weight/maximum_value > Numeric::probthreshold)  { // isgisaxs way
            decor.addParticle(*particle, 0.0, weight/sum_of_weights*m_scale);
        }

        delete particle;
    }

    delete pool;
}
