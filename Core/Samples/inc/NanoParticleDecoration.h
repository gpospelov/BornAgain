#ifndef NANOPARTICLEDECORATION_H
#define NANOPARTICLEDECORATION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticleDecoration.h
//! @brief  Definition of NanoParticleDecoration
//! @author Scientific Computing Group at FRM II
//! @date   23.05.2012

#include "IDecoration.h"
#include "NanoParticle.h"
#include "IInterferenceFunction.h"

//- -------------------------------------------------------------------
//! @class NanoParticleDecoration
//! @brief Definition of decorator class that adds nano particles to ISample objects
//- -------------------------------------------------------------------
class NanoParticleDecoration : public IDecoration
{
public:
	NanoParticleDecoration();
	NanoParticleDecoration(NanoParticle *p_particle);
	NanoParticleDecoration(NanoParticle *p_particle, IInterferenceFunction *p_interference_function);
	virtual ~NanoParticleDecoration();

	/// Clone decoration
	virtual NanoParticleDecoration *clone() const;

	/// Add nano particle
	void addNanoParticle(NanoParticle *p_particle) { m_particles.push_back(p_particle); }

	/// Get number of particles
	size_t getNumberOfParticles() { return m_particles.size(); }

	/// Get particle with index
    NanoParticle* getNanoParticle(size_t index);

    /// Set interference function
    void setInterferenceFunction(IInterferenceFunction* p_interference_function);

    /// Get interference function
    const IInterferenceFunction* getInterferenceFunction() const
    {
        return mp_interference_function;
    }

private:
    std::vector<NanoParticle*> m_particles;
    ///< Vector of the types of nano particles
    IInterferenceFunction* mp_interference_function;
    ///< Currently only a scalar interference function (instead of matrix)
};


#endif // NANOPARTICLEDECORATION_H
