// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleCollection.h
//! @brief     Defines class ParticleCollection.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECOLLECTION_H
#define PARTICLECOLLECTION_H

#include "IParticle.h"
#include "ParameterDistribution.h"

class ParticleInfo;
class DiffuseParticleInfo;

//! @class ParticleCollection
//! @ingroup samples
//! @brief A particle with a form factor and refractive index

class BA_CORE_API_ ParticleCollection : public IParticle
{
public:
    ParticleCollection(const IParticle& prototype,
                       const ParameterDistribution& par_distr);


    virtual ~ParticleCollection() {}
    virtual ParticleCollection *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleCollection *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial* p_material) {
        mP_particle->setAmbientMaterial(p_material);
    }

    //! Returns particle's material.
    virtual const IMaterial* getAmbientMaterial() const {
        return mP_particle->getAmbientMaterial();
    }

    //! Should not be called for objects of this class:
    //! The object should spawn particles that will create the
    //! required form factors
    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const;

    //! Sets _material_.
    virtual void setMaterial(const IMaterial* p_material) {
        if(p_material) {
            mP_particle->setMaterial(p_material);
        }
    }

    //! Returns particle's material.
    virtual const IMaterial* getMaterial() const {
        return mP_particle->getMaterial();
    }

    //! Returns refractive index of the particle
    virtual complex_t getRefractiveIndex() const {
        return mP_particle->getRefractiveIndex();
    }

    //! Returns form factor of the particle originating from its shape only
    virtual const IFormFactor *getSimpleFormFactor() const;


protected:
    std::auto_ptr<IParticle> mP_particle;
    ParameterDistribution m_par_distribution;
    //! Propagates a transformation to child particles
    virtual void applyTransformationToSubParticles(
            const Geometry::Transform3D& transform);
};

#endif // PARTICLECOLLECTION_H


