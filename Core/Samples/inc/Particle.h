// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Particle.h
//! @brief     Defines class Particle.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLE_H
#define PARTICLE_H

#include "ICompositeSample.h"
#include "FormFactorDecoratorMaterial.h"
#include "FormFactorDecoratorTransformation.h"
#include "HomogeneousMaterial.h"

class ParticleInfo;
class DiffuseParticleInfo;

//! A particle with a form factor and refractive index

class BA_CORE_API_ Particle : public ICompositeSample
{
public:
    Particle();
    Particle(const IMaterial* p_material, IFormFactor* p_form_factor = 0);
    Particle(const IMaterial* p_material, const IFormFactor& form_factor);
    Particle(const IMaterial* p_material, const IFormFactor& form_factor,
            const Geometry::PTransform3D &transform);
    virtual ~Particle();
    virtual Particle *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual Particle *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial* p_material)
    {
        mp_ambient_material = p_material;
    }

    //! Create a form factor which includes the particle's shape,
    //! material, ambient material, an optional transformation and an extra
    //! scattering factor
    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const;

    //! Sets _material_ and _thickness_.
    virtual void setMaterial(const IMaterial* p_material) {
        mp_material = p_material;
    }

    //! Returns layer's material.
    virtual const IMaterial* getMaterial() const { return mp_material; }


    //! Returns refractive index of the particle
    virtual complex_t getRefractiveIndex() const
    {
        return (mp_material ? mp_material->getRefractiveIndex()
                            : complex_t(0,0));
    }

    //! Returns transformation.
    const Geometry::PTransform3D getPTransform3D() const
    { return mP_transform; }

    //! Sets transformation.
    virtual void setTransform(const Geometry::PTransform3D& transform)
    { mP_transform = transform; }

    //! Returns form factor of the particle originating from its shape only
    virtual const IFormFactor *getSimpleFormFactor() const {
        return mp_form_factor;
    }

    //! Sets the form factor of the particle (not including scattering factor
    //! from refractive index)
    virtual void setSimpleFormFactor(IFormFactor* p_form_factor);

    //! Creates list of contained particles for diffuse calculations
    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(
            const ParticleInfo& parent_info) const;

    //! Indicates whether the particle consists of an assembly of different
    //! form factors according to a certain distribution
    virtual bool hasDistributedFormFactor() const;

    virtual std::vector<ParticleInfo *> createDistributedParticles(
            size_t samples_per_particle, double factor) const;

protected:
    IFormFactor *createTransformedFormFactor() const;
    const IMaterial* mp_material;
    const IMaterial* mp_ambient_material;
    IFormFactor* mp_form_factor;
    Geometry::PTransform3D mP_transform;
    //!< pointer to the form factor
};

#endif // PARTICLE_H


