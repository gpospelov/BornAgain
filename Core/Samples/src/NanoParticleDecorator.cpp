#include "NanoParticleDecorator.h"

/* ************************************************************************* */
NanoParticleDecorator::NanoParticleDecorator(ISample *p_sub_sample)
: mp_sub_sample(p_sub_sample)
{
}

NanoParticleDecorator::NanoParticleDecorator(ISample* p_sub_sample,
		NanoParticle* p_particle)
: mp_sub_sample(p_sub_sample)
{
	addNanoParticle(p_particle);
}

NanoParticleDecorator::NanoParticleDecorator(ISample* p_sub_sample,
		NanoParticle* p_particle,
		IInterferenceFunction* p_interference_function)
: mp_sub_sample(p_sub_sample)
{
	addNanoParticle(p_particle);
	setInterferenceFunction(p_interference_function);
}

void NanoParticleDecorator::setInterferenceFunction(
		IInterferenceFunction* p_interference_function)
{
	if (mp_interference_function!=p_interference_function) {
		delete mp_interference_function;
		mp_interference_function = p_interference_function;
	}
}



/* ************************************************************************* */
