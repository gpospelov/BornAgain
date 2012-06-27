#include "NanoParticleDecoration.h"
#include "InterferenceFunctionNone.h"

/* ************************************************************************* */
NanoParticleDecoration::NanoParticleDecoration()
: mp_interference_function(0)
, m_total_abundance(0.0)
{
}

NanoParticleDecoration::NanoParticleDecoration(NanoParticle* p_particle, double depth, double abundance)
: mp_interference_function(new InterferenceFunctionNone)
, m_total_abundance(0.0)
{
	addNanoParticle(p_particle, depth, abundance);
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
        p_new->addNanoParticle(m_particles[index].mp_particle->clone(), m_particles[index].m_depth,
                m_particles[index].m_abundance);
    }
    return p_new;
}

void NanoParticleDecoration::addNanoParticle(NanoParticle* p_particle,
        double depth, double abundance)
{
    m_particles.push_back(ParticleInfoStruct(p_particle, depth, abundance));
    m_total_abundance += abundance;
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

double NanoParticleDecoration::getAbundanceFractionOfNanoParticle(
        size_t index) const
{
    if (index<m_particles.size()) {
        return m_particles[index].m_abundance/m_total_abundance;
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
