#ifndef PARTICLEDECORATION_H
#define PARTICLEDECORATION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ParticleDecoration.h
//! @brief  Definition of ParticleDecoration
//! @author Scientific Computing Group at FRM II
//! @date   23.05.2012

#include "IDecoration.h"
#include "Particle.h"
#include "ParticleInfo.h"
#include "IInterferenceFunction.h"
#include "IInterferenceFunctionStrategy.h"
#include "Transform3D.h"

//- -------------------------------------------------------------------
//! @class ParticleDecoration
//! @brief Definition of decorator class that adds particles to ISample objects
//- -------------------------------------------------------------------
class ParticleDecoration : public IDecoration
{
public:
	ParticleDecoration();
	ParticleDecoration(Particle *p_particle, double depth=0.0, double abundance=1.0);
	virtual ~ParticleDecoration();

	/// Clone decoration
	virtual ParticleDecoration *clone() const;

    /// add particle giving depth and transformation
    void addParticle(Particle *p_particle, Geometry::Transform3D *p_transform=0, double depth=0, double abundance=1.0);
    void addParticle(const Particle &particle, const Geometry::Transform3D &transform, double depth=0, double abundance=1.0);

    /// add particle giving depth
    void addParticle(const Particle &particle, double depth=0.0, double abundance=1.0);
    void addParticle(Particle *p_particle, double depth=0.0, double abundance=1.0);

    /// Add particle info
    void addParticleInfo(const ParticleInfo &info);

	/// Get number of particles
	virtual size_t getNumberOfParticles() const { return m_particles.size(); }

    /// get information about particle with index
    virtual const ParticleInfo *getParticleInfo(size_t index) const;

    /// Get abundance fraction of particle with index
    double getAbundanceFractionOfParticle(size_t index) const;

    //! get number of interference functions
    virtual size_t getNumberOfInterferenceFunctions() const {
        return m_interference_functions.size();
    }

    //! get interference functions
    virtual SafePointerVector<IInterferenceFunction> getInterferenceFunctions() const {
        return m_interference_functions;
    }

    /// Add interference function
    void addInterferenceFunction(IInterferenceFunction* p_interference_function);
    void addInterferenceFunction(const IInterferenceFunction &interference_function);

    /// Get interference function with index
    const IInterferenceFunction* getInterferenceFunction(size_t index) const;

private:
    //! adding particle information with simultaneous registration in parent class
    void addAndRegisterParticleInfo(ParticleInfo *child)
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

    //TODO: replace with SafePointerVector
    std::vector<ParticleInfo *> m_particles;
    ///< Vector of the types of particles
    SafePointerVector<IInterferenceFunction> m_interference_functions;
    ///< Currently only a scalar interference function (instead of matrix)
    double m_total_abundance;
};

#endif // PARTICLEDECORATION_H
