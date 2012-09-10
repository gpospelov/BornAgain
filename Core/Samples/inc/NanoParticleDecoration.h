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
#include "Particle.h"
#include "NanoParticleInfo.h"
#include "IInterferenceFunction.h"
#include "IInterferenceFunctionStrategy.h"
#include "Transform3D.h"

//- -------------------------------------------------------------------
//! @class NanoParticleDecoration
//! @brief Definition of decorator class that adds nano particles to ISample objects
//- -------------------------------------------------------------------
class NanoParticleDecoration : public IDecoration
{
public:
	NanoParticleDecoration();
	NanoParticleDecoration(Particle *p_particle, double depth=0.0, double abundance=1.0);
	virtual ~NanoParticleDecoration();

	/// Clone decoration
	virtual NanoParticleDecoration *clone() const;


    /// add nano particle giving depth and transformation
    void addNanoParticle(Particle *p_particle, Geometry::Transform3D *transform=0, double depth=0, double abundance=1.0);
    void addNanoParticle(const Particle &p_particle, const Geometry::Transform3D &transform, double depth=0, double abundance=1.0);

    /// add nano particle giving depth
    void addNanoParticle(const Particle &p_particle, double depth=0.0, double abundance=1.0);
    void addNanoParticle(Particle *p_particle, double depth=0.0, double abundance=1.0);

    /// Add nano particle info
    void addNanoParticleInfo(const NanoParticleInfo &p_info);

	/// Get number of particles
	size_t getNumberOfParticles() const { return m_particles.size(); }

    /// get information about nano particle with index
    const NanoParticleInfo *getNanoParticleInfo(size_t index) const;

    /// Get abundance fraction of particle with index
    double getAbundanceFractionOfNanoParticle(size_t index) const;


    /// Add interference function
    void addInterferenceFunction(IInterferenceFunction* p_interference_function);
    void addInterferenceFunction(const IInterferenceFunction &interference_function);

    /// Get interference function with index
    const IInterferenceFunction* getInterferenceFunction(size_t index) const;


    /// Create interference function strategy
    IInterferenceFunctionStrategy *createStrategy(const std::vector<IFormFactor *> &form_factors) const;

    /// Get surface density of all particles
    double getTotalParticleSurfaceDensity() const { return m_total_particle_surface_density; }

    /// Set surface density of all particles
    void setTotalParticleSurfaceDensity(double surface_density) { m_total_particle_surface_density = surface_density; }

private:
    /// copy constructor and assignment operator are hidden since there is a clone method
    NanoParticleDecoration(const NanoParticleDecoration &);
    NanoParticleDecoration &operator=(const NanoParticleDecoration &);

    //! adding nano particle information with simultaneous registration in parent class
    void addAndRegisterNanoParticleInfo(NanoParticleInfo *child)
    {
        m_total_abundance += child->getAbundance();
        m_particles.push_back(child);
        registerChild(child);
    }

    //! adding interference function with simultaneous registration in parent class
    void addAndRegisterInterferenceFunction(IInterferenceFunction *child)
    {
        m_interference_functions.push_back(child);
        registerChild(child);
    }

    std::vector<NanoParticleInfo *> m_particles;
    ///< Vector of the types of nano particles
    std::vector<IInterferenceFunction *> m_interference_functions;
    ///< Currently only a scalar interference function (instead of matrix)
    double m_total_abundance;
    ///< To guarantee that fractions sum up to 1
    double m_total_particle_surface_density;
};


#endif // NANOPARTICLEDECORATION_H
