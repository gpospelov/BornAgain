// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IParticle.h
//! @brief     Defines interface IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARTICLE_H
#define IPARTICLE_H

#include "ICompositeSample.h"
#include "IMaterial.h"

#include <memory>
#include <boost/scoped_ptr.hpp>

class ParticleInfo;

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
    virtual void setAmbientMaterial(const IMaterial& material) {
        (void)material;
    }

    //! Returns particle's material.
    virtual const IMaterial* getAmbientMaterial() const=0;

    //! Create a form factor which includes the particle's shape,
    //! material, ambient material, an optional transformation and an extra
    //! scattering factor
    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const=0;

    //! Returns transformation.
    const Geometry::Transform3D *getTransform3D() const {
        return mP_transform.get();
    }

    //! Sets transformation.
    virtual void setTransformation(const Geometry::Transform3D& transform);

    //! Applies transformation by composing it with the existing one
    virtual void applyTransformation(const Geometry::Transform3D& transform);

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
