#include "NanoParticleDecoration.h"
#include "InterferenceFunctionNone.h"

/* ************************************************************************* */
NanoParticleDecoration::NanoParticleDecoration()
: mp_interference_function(0)
{
}

NanoParticleDecoration::NanoParticleDecoration(NanoParticle* p_particle, double depth)
: mp_interference_function(new InterferenceFunctionNone)
{
	addNanoParticle(p_particle, depth);
}

NanoParticleDecoration::NanoParticleDecoration(NanoParticle* p_particle, double depth,
		IInterferenceFunction* p_interference_function)
: mp_interference_function(0)
{
	addNanoParticle(p_particle, depth);
	setInterferenceFunction(p_interference_function);
}

NanoParticleDecoration::~NanoParticleDecoration()
{
    delete mp_interference_function;
}

NanoParticleDecoration* NanoParticleDecoration::clone() const
{
    NanoParticleDecoration *p_new = new NanoParticleDecoration();
    p_new->setInterferenceFunction(mp_interference_function->clone());
    for (size_t index=0; index<m_particles.size(); ++index) {
        p_new->addNanoParticle(m_particles[index].mp_particle->clone(), m_particles[index].m_depth);
    }
    return p_new;
}

NanoParticle* NanoParticleDecoration::getNanoParticle(size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index].mp_particle->clone();
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

void NanoParticleDecoration::setInterferenceFunction(
		IInterferenceFunction* p_interference_function)
{
	if (mp_interference_function!=p_interference_function) {
		delete mp_interference_function;
		mp_interference_function = p_interference_function;
	}
}

NanoParticleDecoration::ParticleDepthStruct::ParticleDepthStruct(
        NanoParticle* p_particle, double depth)
: mp_particle(p_particle)
, m_depth(depth)
{
}

NanoParticleDecoration::ParticleDepthStruct::ParticleDepthStruct(
        const ParticleDepthStruct& source)
: mp_particle(source.mp_particle->clone())
, m_depth(source.m_depth)
{
}

NanoParticleDecoration::ParticleDepthStruct::~ParticleDepthStruct()
{
    delete mp_particle;
}

const NanoParticleDecoration::ParticleDepthStruct& NanoParticleDecoration::ParticleDepthStruct::operator =(
        const ParticleDepthStruct& right)
{
    if (this!=&right) {
        delete mp_particle;
        mp_particle = right.mp_particle->clone();
        m_depth = right.m_depth;
    }
    return *this;
}





/* ************************************************************************* */
