// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/ParticleLayout.h
//! @brief     Declares class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUT_H
#define PARTICLELAYOUT_H

#include "ILayout.h"
#include "Particle.h"
#include "IInterferenceFunction.h"
#include "Rotations.h"

#include <memory>

//! @class ParticleLayout
//! @ingroup samples
//! @brief Decorator class that adds particles to ISample objects

class BA_CORE_API_ ParticleLayout : public ILayout
{
public:
    ParticleLayout();
    ParticleLayout(const IAbstractParticle &particle);
    ParticleLayout(const IAbstractParticle &particle, double abundance);

    virtual ~ParticleLayout();

    virtual ParticleLayout *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleLayout *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! @brief Adds generic particle to the layout
    virtual void addParticle(const IAbstractParticle &particle);

    //! @brief Adds generic particle to the layout with only abundance defined
    //! @param abundance Particle abundance
    virtual void addParticle(const IAbstractParticle &particle, double abundance);

    //! @brief Adds particle to the layout with abundance and position defined
    //! @param abundance Particle abundance
    //! @param position Particle position
    virtual void addParticle(const IParticle &particle, double abundance,
                             const kvector_t position);

    //! @brief Adds particle to the layout with abundance, position and the rotation defined
    //! @param abundance Particle abundance
    //! @param position Particle position
    //! @param rotation Particle rotation
    virtual void addParticle(const IParticle &particle, double abundance,
                             const kvector_t position, const IRotation& rotation);

    //! Returns number of particles
    virtual size_t getNumberOfParticles() const;

    //! get information about particle with index
    virtual const IAbstractParticle *getParticle(size_t index) const;

    //! Returns information on all particles (type and abundance)
    //! and generates new particles if an IAbstractParticle denotes a collection
    virtual SafePointerVector<const IParticle> getParticles() const;

    //! Get abundance fraction of particle with index
    double getAbundanceOfParticle(size_t index) const;

    //! Returns interference functions
    virtual const IInterferenceFunction* getInterferenceFunction() const;

    //! Sets interference function
    void addInterferenceFunction(const IInterferenceFunction &interference_function);

    //! Returns surface density of all particles
    virtual double getTotalParticleSurfaceDensity() const;

    //! Sets surface density of all particles
    virtual void setTotalParticleSurfaceDensity(double particle_density);

private:
    //! Adds particle information with simultaneous registration in parent class.
    void addAndRegisterAbstractParticle(IAbstractParticle *child);

    //! Sets interference function with simultaneous registration in parent class
    void setAndRegisterInterferenceFunction(IInterferenceFunction *child);

    void print(std::ostream &ostr) const;

    //! Vector of the types of particles
    SafePointerVector<IAbstractParticle> m_particles;

    //! Interference function
    std::unique_ptr<IInterferenceFunction> mP_interference_function;

    //! Total particle surface density
    double m_total_particle_density;
};

#endif // PARTICLEDECORATION_H
