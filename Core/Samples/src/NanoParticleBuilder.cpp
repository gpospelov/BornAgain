#include "NanoParticleBuilder.h"
#include "NanoParticleDecoration.h"
#include "Numeric.h"
#include "StochasticSampledParameter.h"

#include <numeric>
#include <algorithm>

NanoParticleBuilder::NanoParticleBuilder() :
    m_prototype(0), m_parameter(0), m_scale(0)
{
}


NanoParticleBuilder::~NanoParticleBuilder()
{
    delete m_prototype;
    delete m_parameter;
}


/* ************************************************************************* */
//set prototype for nano particle production
/* ************************************************************************* */
void NanoParticleBuilder::setPrototype(const NanoParticle &particle, std::string name, const StochasticParameter<double> &param, double scale)
{
    delete m_prototype;
    m_prototype = particle.clone();
    m_parameter_name = name;
    delete m_parameter;
    m_parameter = param.clone();
    m_scale = scale;
}


/* ************************************************************************* */
// plant nano particles in given decoration
/* ************************************************************************* */
void NanoParticleBuilder::plantNanoParticles(NanoParticleDecoration &decor)
{
    if( !m_prototype ) throw NullPointerException("NanoParticleBuilder::plantNanoParticle() -> Error. No prototype is defined");

    if( !m_parameter ) throw NullPointerException("NanoParticleBuilder::plantNanoParticle() -> Error. No parameter is defined");

    ParameterPool *pool = m_prototype->createParameterTree();

    StochasticSampledParameter *sampled_parameter = dynamic_cast<StochasticSampledParameter *>(m_parameter);
    if( !sampled_parameter) {
        throw LogicErrorException("NanoParticleBuilder::plantNanoParticle() -> Error. Not supported parameter type");
    }

    std::vector<double> weights;
    for(size_t i=0; i<sampled_parameter->getNbins(); ++i) weights.push_back(sampled_parameter->probabilityBinDensity(i));
    double maximum_value = *std::max_element(weights.begin(), weights.end());
    double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);

    for(size_t i=0; i<sampled_parameter->getNbins(); ++i) {

        double weight = sampled_parameter->probabilityBinDensity(i);
        double value = sampled_parameter->getBinValue(i);

        // changing value of the parameter and making clone
        pool->setParameterValue(m_parameter_name, value);
        NanoParticle *particle = m_prototype->clone();

        if(weight/maximum_value > Numeric::probthreshold)  { // isgisaxs way
            decor.addNanoParticle(*particle, 0.0, weight/sum_of_weights*m_scale);
        }

        delete particle;
    }

    delete pool;

}
