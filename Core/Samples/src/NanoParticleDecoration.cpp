#include "NanoParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "DecouplingApproximationStrategy.h"
#include "LocalMonodisperseApproximationStrategy.h"

/* ************************************************************************* */
NanoParticleDecoration::NanoParticleDecoration()
: m_total_abundance(0.0)
{
}

NanoParticleDecoration::NanoParticleDecoration(NanoParticle* p_particle, double depth, double abundance)
: m_total_abundance(0.0)
{
	addNanoParticle(p_particle, depth, abundance);
}

NanoParticleDecoration::~NanoParticleDecoration()
{
    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        delete m_interference_functions[i];
    }
}


NanoParticleDecoration* NanoParticleDecoration::clone() const
{
    NanoParticleDecoration *p_new = new NanoParticleDecoration();
    for (size_t index=0; index<m_particles.size(); ++index) {
        p_new->addNanoParticle(m_particles[index].mp_particle->clone(), m_particles[index].m_depth,
                m_particles[index].m_abundance);
    }
    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        p_new->addInterferenceFunction(m_interference_functions[i]->clone());
    }
    return p_new;
}

void NanoParticleDecoration::addNanoParticle(NanoParticle* p_particle,
        double depth, double abundance)
{
    m_particles.push_back(ParticleInfoStruct(p_particle, depth, abundance));
    m_total_abundance += abundance;
}

const NanoParticle* NanoParticleDecoration::getNanoParticle(size_t index) const
{
    if (index<m_particles.size()) {
        //return m_particles[index].mp_particle->clone();
        return m_particles[index].mp_particle;
    }
    throw OutOfBoundsException("Not so many particles in this decoration.");
}

double NanoParticleDecoration::getDepthOfNanoParticle(size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index].m_depth;
    }
    throw OutOfBoundsException("Not so many particles in this decoration.");
}

double NanoParticleDecoration::getAbundanceFractionOfNanoParticle(
        size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index].m_abundance/m_total_abundance;
    }
    throw OutOfBoundsException("Not so many particles in this decoration.");
}

void NanoParticleDecoration::addInterferenceFunction(
		IInterferenceFunction* p_interference_function)
{
    m_interference_functions.push_back(p_interference_function);
}

const IInterferenceFunction* NanoParticleDecoration::getInterferenceFunction(
        size_t index) const
{
    if (index<m_interference_functions.size()) {
        return m_interference_functions[index]->clone();
    }
    throw OutOfBoundsException("Not so many interference functions in this decoration.");
}

IInterferenceFunctionStrategy* NanoParticleDecoration::createStrategy(
        const std::vector<IFormFactor*>& form_factors) const
{
    std::vector<double> fractions;
    for (size_t i=0; i<m_particles.size(); ++i) {
        fractions.push_back(getAbundanceFractionOfNanoParticle(i));
    }
    IInterferenceFunctionStrategy *p_strategy;
    size_t n_particles = m_particles.size();
    size_t n_ifs = m_interference_functions.size();
    if (n_ifs==1) {
        p_strategy = new DecouplingApproximationStrategy();
    }
    else if (n_ifs==n_particles) {
        p_strategy = new LocalMonodisperseApproximationStrategy();
    }
    else {
        throw ClassInitializationException("Could not create interference function strategy with given parameters.");
    }
    p_strategy->init(form_factors, fractions, m_interference_functions);
    return p_strategy;
}

NanoParticleDecoration::ParticleInfoStruct::ParticleInfoStruct(
        NanoParticle* p_particle, double depth, double abundance)
: mp_particle(p_particle)
, m_depth(depth)
, m_abundance(abundance)
{
}

NanoParticleDecoration::ParticleInfoStruct::ParticleInfoStruct(
        const ParticleInfoStruct& source)
: mp_particle(source.mp_particle->clone())
, m_depth(source.m_depth)
, m_abundance(source.m_abundance)
{
}

NanoParticleDecoration::ParticleInfoStruct::~ParticleInfoStruct()
{
    delete mp_particle;
}

const NanoParticleDecoration::ParticleInfoStruct& NanoParticleDecoration::ParticleInfoStruct::operator =(
        const ParticleInfoStruct& right)
{
    if (this!=&right) {
        delete mp_particle;
        mp_particle = right.mp_particle->clone();
        m_depth = right.m_depth;
        m_abundance = right.m_abundance;
    }
    return *this;
}




/* ************************************************************************* */
