// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleLayout.h
//! @brief     Defines class ParticleLayout.
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
#include "ParticleInfo.h"
#include "IInterferenceFunction.h"
#include "Rotations.h"

#include <boost/shared_ptr.hpp>

//! @class ParticleLayout
//! @ingroup samples
//! @brief Decorator class that adds particles to ISample objects

class BA_CORE_API_ ParticleLayout : public ILayout
{
public:
    ParticleLayout();
    ParticleLayout(const IAbstractParticle &particle, double abundance = 1.);

    virtual ~ParticleLayout();

    virtual ParticleLayout *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleLayout *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const
    {
        visitor->visit(this);
    }

    //! @brief Adds generic particle to the layout with only abundance defined
    //! @param abundance Particle abundance
    virtual void addParticle(const IAbstractParticle &particle, double abundance = 1.0);

    //! @brief Adds particle to the layout with abundance and position defined
    //! @param abundance Particle abundance
    //! @param position Particle position
    virtual void addParticle(const IParticle &particle, double abundance,
                             const kvector_t &position);

    //! @brief Adds particle to the layout with abundance, position and the rotation defined
    //! @param abundance Particle abundance
    //! @param position Particle position
    //! @param rotation Particle rotation
    virtual void addParticle(const IParticle &particle, double abundance,
                             const kvector_t &position, const IRotation& rotation);

    //! Returns number of particles
    virtual size_t getNumberOfParticles() const
    {
        return m_particles.size();
    }

    //! get information about particle with index
    virtual const IAbstractParticle *getParticle(size_t index) const;

    //! Returns information on all particles (type and abundance)
    //! and generates new particles if an IAbstractParticle denotes a collection
    virtual void getParticleInfos(SafePointerVector<const IParticle>& particle_vector,
                                  std::vector<double>& abundance_vector) const;

    //! Get abundance fraction of particle with index
    double getAbundanceOfParticle(size_t index) const;

    //! Returns number of interference functions
    virtual size_t getNumberOfInterferenceFunctions() const
    {
        return m_interference_functions.size();
    }

    //! Returns interference functions
    virtual SafePointerVector<IInterferenceFunction> getInterferenceFunctions() const
    {
        return m_interference_functions;
    }

    //! Adds interference function
    void addInterferenceFunction(IInterferenceFunction *p_interference_function);

    void addInterferenceFunction(const IInterferenceFunction &interference_function);

    //! Returns interference function with index
    const IInterferenceFunction *getInterferenceFunction(size_t index) const;

private:
    //! Adds particle information with simultaneous registration in parent class.
    void addAndRegisterParticleInfo(ParticleInfo *child);

    //! Adds interference function with simultaneous registration in parent class
    void addAndRegisterInterferenceFunction(IInterferenceFunction *child);

    void print(std::ostream &ostr) const;

    //! Vector of the types of particles
    SafePointerVector<ParticleInfo> m_particles;

    //! Vector of interference functions
    SafePointerVector<IInterferenceFunction> m_interference_functions;
};

#endif // PARTICLEDECORATION_H
