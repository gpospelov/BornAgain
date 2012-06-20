#ifndef NANOPARTICLEDECORATOR_H
#define NANOPARTICLEDECORATOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticleDecorator.h
//! @brief  Definition of NanoParticleDecorator
//! @author Scientific Computing Group at FRM II
//! @date   23.05.2012

#include "NanoParticle.h"
#include "IInterferenceFunction.h"

//- -------------------------------------------------------------------
//! @class NanoParticleDecorator
//! @brief Definition of decorator class that adds nano particles to ISample objects
//- -------------------------------------------------------------------
class NanoParticleDecorator : public ISample
{
public:
	NanoParticleDecorator(ISample *p_sub_sample);
	NanoParticleDecorator(ISample *p_sub_sample, NanoParticle *p_particle);
	NanoParticleDecorator(ISample *p_sub_sample, NanoParticle *p_particle, IInterferenceFunction *p_interference_function);
	virtual ~NanoParticleDecorator() {}

	/// Return decorated sample
	ISample* getSubSample() const { return mp_sub_sample; }

	/// Add nano particle
	void addNanoParticle(NanoParticle *p_particle) { m_particles.push_back(p_particle); }

	/// Get number of particles
	size_t getNumberOfParticles() { return m_particles.size(); }

	/// Set interference function
	void setInterferenceFunction(IInterferenceFunction *p_interference_function);
private:
	std::vector<NanoParticle *> m_particles;  ///< Vector of the types of nano particles
	IInterferenceFunction *mp_interference_function;  ///< Currently only a scalar interference function (instead of matrix)
    ISample* mp_sub_sample;                   ///< Decorated ISample object
};


#endif // NANOPARTICLEDECORATOR_H
