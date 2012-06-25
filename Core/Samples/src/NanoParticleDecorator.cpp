#include "NanoParticleDecoration.h"

/* ************************************************************************* */
NanoParticleDecoration::NanoParticleDecoration()
{
}

NanoParticleDecoration::NanoParticleDecoration(NanoParticle* p_particle)
{
	addNanoParticle(p_particle);
}

NanoParticleDecoration::NanoParticleDecoration(NanoParticle* p_particle,
		IInterferenceFunction* p_interference_function)
{
	addNanoParticle(p_particle);
	setInterferenceFunction(p_interference_function);
}

NanoParticleDecoration::~NanoParticleDecoration()
{
    delete mp_interference_function;
    for (std::vector<NanoParticle*>::iterator it=m_particles.begin(); it!=m_particles.end(); ++it) {
        delete *it;
    }
    m_particles.clear();
}

NanoParticleDecoration* NanoParticleDecoration::clone() const
{
    NanoParticleDecoration *p_new = new NanoParticleDecoration();
    p_new->setInterferenceFunction(mp_interference_function->clone());
    for (size_t index=0; index<m_particles.size(); ++index) {
        p_new->addNanoParticle(m_particles[index]->clone());
    }
    return p_new;
}

NanoParticle* NanoParticleDecoration::getNanoParticle(size_t index)
{
    if (index<m_particles.size()) {
        return m_particles[index];
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



/* ************************************************************************* */
