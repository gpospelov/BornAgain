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
	NanoParticleDecoration(NanoParticle *p_particle, double depth=0.0, double abundance=1.0);
	virtual ~NanoParticleDecoration();

	/// Clone decoration
	virtual NanoParticleDecoration *clone() const;

	/// Add nano particle
	void addNanoParticle(NanoParticle *p_particle, double depth=0.0, double abundance=1.0);

	/// Get number of particles
	size_t getNumberOfParticles() const { return m_particles.size(); }

	/// Get particle with index
    NanoParticle* getNanoParticle(size_t index) const;

    /// Get depth of particle with index
    double getDepthOfNanoParticle(size_t index) const;

    /// Get abundance fraction of particle with index
    double getAbundanceFractionOfNanoParticle(size_t index) const;

    /// Set interference function
    void setInterferenceFunction(IInterferenceFunction* p_interference_function);

    /// Get interference function
    const IInterferenceFunction* getInterferenceFunction() const
    {
        return mp_interference_function;
    }

private:
    struct ParticleInfoStruct
    {
        ParticleInfoStruct(NanoParticle *p_particle, double depth, double abundance);
        ParticleInfoStruct(const ParticleInfoStruct &source);
        ~ParticleInfoStruct();

        const ParticleInfoStruct &operator=(const ParticleInfoStruct &right);
        NanoParticle *mp_particle;
        double m_depth;
        double m_abundance;
    };
    std::vector<ParticleInfoStruct> m_particles;
    ///< Vector of the types of nano particles
    IInterferenceFunction* mp_interference_function;
    ///< Currently only a scalar interference function (instead of matrix)
    double m_total_abundance;
    ///< To guarantee that fractions sum up to 1
};


#endif // NANOPARTICLEDECORATION_H
