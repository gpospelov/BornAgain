// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleDecoration.h
//! @brief     Defines class ParticleDecoration.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef PARTICLEDECORATION_H
#define PARTICLEDECORATION_H

#include "IDecoration.h"
#include "Particle.h"
#include "ParticleInfo.h"
#include "IInterferenceFunction.h"

//! Decorator class that adds particles to ISample objects

class ParticleDecoration : public IDecoration
{
 public:
    ParticleDecoration();
    ParticleDecoration(
        Particle *p_particle, double depth=0.0, double abundance=1.0);
    ParticleDecoration(
        const Particle& p_particle, double depth=0.0, double abundance=1.0);
    virtual ~ParticleDecoration();

    virtual ParticleDecoration *clone() const;

    //! Adds particle giving depth and transformation
    void addParticle(
        Particle *p_particle, Geometry::ITransform3D *p_transform=0,
        double depth=0, double abundance=1.0);
    void addParticle(
        const Particle& particle, const Geometry::ITransform3D& transform,
        double depth=0, double abundance=1.0);

    //! Adds particle giving depth
    void addParticle(
        const Particle& particle, double depth=0.0, double abundance=1.0);
    void addParticle(
        Particle *p_particle, double depth=0.0, double abundance=1.0);

    //! Adds particle info
    void addParticleInfo(const ParticleInfo& info);

    //! Returns number of particles
    virtual size_t getNumberOfParticles() const { return m_particles.size(); }

    /// get information about particle with index
    virtual const ParticleInfo *getParticleInfo(size_t index) const;

    /// Get abundance fraction of particle with index
    double getAbundanceFractionOfParticle(size_t index) const;

    //! Returns number of interference functions
    virtual size_t getNumberOfInterferenceFunctions() const
    { return m_interference_functions.size(); }

    //! Returns interference functions
    virtual SafePointerVector<IInterferenceFunction>
        getInterferenceFunctions() const
    { return m_interference_functions; }

    //! Adds interference function
    void addInterferenceFunction(
        IInterferenceFunction* p_interference_function);

    void addInterferenceFunction(
        const IInterferenceFunction& interference_function);

    //! Returns interference function with index
    const IInterferenceFunction* getInterferenceFunction(size_t index) const;

 private:
    //! Adds particle information with simultaneous registration in parent class.
    void addAndRegisterParticleInfo(ParticleInfo *child)
    {
        m_total_abundance += child->getAbundance();
        m_particles.push_back(child);
        registerChild(child);
    }

    //! Adds interference function with simultaneous registration in parent class
    void addAndRegisterInterferenceFunction(IInterferenceFunction *child)
    {
        m_interference_functions.push_back(child);
        registerChild(child);
    }

    //TODO: replace with SafePointerVector
    std::vector<ParticleInfo *> m_particles;

    //! Vector of the types of particles
    SafePointerVector<IInterferenceFunction> m_interference_functions;

    //! Currently only a scalar interference function (instead of matrix)
    double m_total_abundance;
};

#endif // PARTICLEDECORATION_H
