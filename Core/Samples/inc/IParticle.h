// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IParticle.h
//! @brief     Defines interface IParticle.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARTICLE_H
#define IPARTICLE_H

#include "ICompositeSample.h"
#include "IMaterial.h"

#include <memory>
#include <boost/scoped_ptr.hpp>

//! @class IParticle
//! @ingroup samples
//! @brief Interface for a generic particle

class BA_CORE_API_ IParticle : public ICompositeSample
{
public:
    virtual ~IParticle() {}
    virtual IParticle *clone() const=0;

    //! Returns a clone with inverted magnetic fields
    virtual IParticle *cloneInvertB() const=0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial* p_material) {
        (void)p_material;
    }

    //! Returns particle's material.
    virtual const IMaterial* getAmbientMaterial() const=0;

    //! Create a form factor which includes the particle's shape,
    //! material, ambient material, an optional transformation and an extra
    //! scattering factor
    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const=0;

    //! Sets _material_ .
    virtual void setMaterial(const IMaterial* p_material) {
        (void)p_material;
    }

    //! Returns particle's material.
    virtual const IMaterial* getMaterial() const=0;

    //! Returns refractive index of the particle
    virtual complex_t getRefractiveIndex() const=0;

    //! Returns transformation.
    const Geometry::Transform3D *getPTransform3D() const {
        return mP_transform.get();
    }

    //! Sets transformation.
    virtual void setTransformation(const Geometry::Transform3D& transform);

    //! Applies transformation by composing it with the existing one
    virtual void applyTransformation(const Geometry::Transform3D& transform);

    //! Returns form factor of the particle originating from its shape only
    virtual const IFormFactor *getSimpleFormFactor() const=0;

    //! Sets the form factor of the particle (not including scattering factor
    //! from refractive index)
    virtual void setSimpleFormFactor(IFormFactor* p_form_factor) {
        (void)p_form_factor;
    }

    //! Creates list of contained particles for diffuse calculations
    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(
            const ParticleInfo& parent_info) const {
        (void)parent_info;
        return 0;
    }

    //! Indicates whether the particle consists of an assembly of different
    //! form factors according to a certain distribution
    virtual bool hasDistributedFormFactor() const {
        return false;
    }

    virtual std::vector<ParticleInfo *> createDistributedParticles(
            size_t samples_per_particle, double factor) const {
        (void)samples_per_particle;
        (void)factor;
        std::vector<ParticleInfo *> result;
        return result;
    }

protected:
    virtual void applyTransformationToSubParticles(
            const Geometry::Transform3D& transform)=0;
    std::auto_ptr<Geometry::Transform3D> mP_transform;
};


inline void IParticle::setTransformation(const Geometry::Transform3D &transform)
{
    if (!mP_transform.get()) {
        mP_transform.reset(transform.clone());
        applyTransformationToSubParticles(transform);
        return;
    }
    boost::scoped_ptr<Geometry::Transform3D> P_inverse(
            mP_transform->createInverse());
    applyTransformationToSubParticles(*P_inverse);
    mP_transform.reset(transform.clone());
    applyTransformationToSubParticles(transform);
}

inline void IParticle::applyTransformation(const Geometry::Transform3D &transform)
{
    Geometry::Transform3D total_transformation;
    if (mP_transform.get()) {
        total_transformation = transform * (*mP_transform);
    }
    else {
        total_transformation = transform;
    }
    mP_transform.reset(total_transformation.clone());
    applyTransformationToSubParticles(transform);
}

#endif // IPARTICLE_H
