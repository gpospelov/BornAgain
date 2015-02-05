// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Particle.h
//! @brief     Defines class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLE_H
#define PARTICLE_H

#include "IParticle.h"
#include "FormFactorDecoratorMaterial.h"
#include "FormFactorDecoratorTransformation.h"
#include "IMaterial.h"

class ParticleInfo;

//! @class Particle
//! @ingroup samples
//! @brief A particle with a form factor and refractive index

class BA_CORE_API_ Particle : public IParticle
{
public:
    Particle();
    Particle(const IMaterial &p_material);
    Particle(const IMaterial &p_material, const IFormFactor &form_factor);
    Particle(const IMaterial &p_material, const IFormFactor &form_factor,
            const Geometry::Transform3D &transform);

    virtual ~Particle();
    virtual Particle *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual Particle *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial& material)
    {
        if(mp_ambient_material != &material) {
            delete mp_ambient_material;
            mp_ambient_material = material.clone();
        }
    }

    //! Returns particle's material.
    virtual const IMaterial* getAmbientMaterial() const { return mp_ambient_material; }

    //! Create a form factor which includes the particle's shape,
    //! material, ambient material, an optional transformation and an extra
    //! scattering factor
    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const;

    //! Sets _material_.
    virtual void setMaterial(const IMaterial& material) {
        if(mp_material != &material) {
            delete mp_material;
            mp_material = material.clone();
        }
    }

    //! Returns particle's material.
    virtual const IMaterial* getMaterial() const { return mp_material; }

    //! Returns refractive index of the particle
    virtual complex_t getRefractiveIndex() const
    {
        return (mp_material ? mp_material->getRefractiveIndex()
                            : complex_t(0,0));
    }

    //! Sets the form factor
    void setFormFactor(const IFormFactor& form_factor);

    //! Returns the form factor
    const IFormFactor* getFormFactor() const {
        return mp_form_factor;
    }

protected:
    IFormFactor *createTransformedFormFactor() const;
    //! Propagates a transformation to child particles
    virtual void applyTransformationToSubParticles(
            const Geometry::Transform3D& transform);
    IMaterial* mp_material;
    IMaterial* mp_ambient_material;
    IFormFactor* mp_form_factor;
};

#endif // PARTICLE_H


