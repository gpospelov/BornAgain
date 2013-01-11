#ifndef ISGISAXSMORPHOLOGYFILEDECORATION_H_
#define ISGISAXSMORPHOLOGYFILEDECORATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IsGISAXSMorphologyFileDecoration.h
//! @brief  Definition of IsGISAXSMorphologyFileDecoration class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 7, 2013

#include "IDecoration.h"
#include "Particle.h"
#include "PositionParticleInfo.h"
#include "IInterferenceFunction.h"
#include "IInterferenceFunctionStrategy.h"
#include "Transform3D.h"
#include "SafePointerVector.h"

//- -------------------------------------------------------------------
//! @class IsGISAXSMorphologyFileDecoration
//! @brief Definition of decorator class that mimics the behaviour of
//! IsGISAXS morphology files
//- -------------------------------------------------------------------
class IsGISAXSMorphologyFileDecoration : public IDecoration
{
public:
    IsGISAXSMorphologyFileDecoration();
    virtual ~IsGISAXSMorphologyFileDecoration();

    /// Clone decoration
    virtual IsGISAXSMorphologyFileDecoration *clone() const;

    /// add particle giving depth and transformation
    void addParticle(Particle *p_particle, Geometry::Transform3D *p_transform, kvector_t position, double abundance=1.0);
    void addParticle(const Particle &particle, const Geometry::Transform3D &transform, kvector_t position, double abundance=1.0);

    /// add particle giving depth
    void addParticle(const Particle &particle, kvector_t position, double abundance=1.0);
    void addParticle(Particle *p_particle, kvector_t position, double abundance=1.0);

    /// Add particle info
    void addParticleInfo(const PositionParticleInfo &info);

    /// Get number of particles
    virtual size_t getNumberOfParticles() const { return m_particles.size(); }

    /// get information about particle with index
    virtual const PositionParticleInfo *getParticleInfo(size_t index) const;

    /// Get abundance fraction of particle with index
    double getAbundanceFractionOfParticle(size_t index) const;

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
    IsGISAXSMorphologyFileDecoration(const IsGISAXSMorphologyFileDecoration &);
    IsGISAXSMorphologyFileDecoration &operator=(const IsGISAXSMorphologyFileDecoration &);

    //! adding particle information with simultaneous registration in parent class
    void addAndRegisterParticleInfo(PositionParticleInfo *child)
    {
        m_total_abundance += child->getAbundance();
        m_particles.push_back(child);
        registerChild(child);
    }

    //! adding interference function with simultaneous registration in parent class
    void addAndRegisterInterferenceFunction(IInterferenceFunction *child)
    {
        if (m_interference_functions.size() > 0) {
            throw ClassInitializationException("IsGISAXSMorphologyFileDecoration does not allow more than one interference function");
        }
        m_interference_functions.push_back(child);
        registerChild(child);
    }

    SafePointerVector<PositionParticleInfo> m_particles;
    ///< Vector of the types of particles
    SafePointerVector<IInterferenceFunction> m_interference_functions;
    ///< Currently only a scalar interference function (instead of matrix)
    double m_total_abundance;
    ///< Sum of individual fractions (does not need to be 1)
    double m_total_particle_surface_density;
};

#endif /* ISGISAXSMORPHOLOGYFILEDECORATION_H_ */
