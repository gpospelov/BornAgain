// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/ParticleDistribution.h
//! @brief     Defines class ParticleDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTION_H
#define PARTICLEDISTRIBUTION_H

#include "IParticle.h"
#include "ParameterDistribution.h"
#include "SafePointerVector.h"

//! @class ParticleDistribution
//! @ingroup samples
//! @brief A particle with a form factor and refractive index

class BA_CORE_API_ ParticleDistribution : public IAbstractParticle
{
public:
    ParticleDistribution(const IParticle &prototype, const ParameterDistribution &par_distr);

    virtual ParticleDistribution *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleDistribution *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial &material);

    //! Returns particle's material.
    virtual const IMaterial *getAmbientMaterial() const;

    //! Initializes list of new particles generated according to a distribution
    virtual void generateParticles(std::vector<const IParticle *> &particle_vector) const;

    //! Returns the distributed parameter data
    ParameterDistribution getParameterDistribution() const;

    //! Returns the parameter pool that can be used for parameter distributions
    ParameterPool *createDistributedParameterPool() const;

    //! Returns particle.
    const IParticle *getParticle() const;

private:
    std::unique_ptr<IParticle> mP_particle;
    ParameterDistribution m_par_distribution;
};

#endif // PARTICLEDISTRIBUTION_H
