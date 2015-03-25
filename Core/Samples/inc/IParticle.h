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
#include "Rotations.h"

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

    //! Returns rotation object
    const IRotation* getRotation() const {
        return mP_rotation.get();
    }
    //! Returns transformation.
    const Geometry::Transform3D getTransform3D() const {
        if (mP_rotation.get()) return mP_rotation->getTransform3D();
        return Geometry::Transform3D();
    }

    //! Sets transformation.
    void setTransformation(const Geometry::Transform3D& transform);

    //! Applies transformation by composing it with the existing one
    void applyTransformation(const Geometry::Transform3D& transform);

protected:
    virtual void applyTransformationToSubParticles(
            const Geometry::Transform3D& transform)=0;
    std::auto_ptr<IRotation> mP_rotation;
};


inline void IParticle::setTransformation(const Geometry::Transform3D &transform)
{
    if (!mP_rotation.get()) {
        mP_rotation.reset(IRotation::createRotation(transform));
        applyTransformationToSubParticles(transform);
        return;
    }
    Geometry::Transform3D inverse_transform = mP_rotation->getTransform3D().getInverse();
    applyTransformationToSubParticles(inverse_transform);
    mP_rotation.reset(IRotation::createRotation(transform));
    applyTransformationToSubParticles(transform);
}

inline void IParticle::applyTransformation(const Geometry::Transform3D &transform)
{
    IRotation *p_rotation = IRotation::createRotation(transform);
    if (mP_rotation.get()) {
        mP_rotation.reset(CreateProduct(*p_rotation, *mP_rotation));
        delete p_rotation;
    }
    else {
        mP_rotation.reset(p_rotation);
    }
    applyTransformationToSubParticles(transform);
}

#endif // IPARTICLE_H
