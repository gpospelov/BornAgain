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
#include "FormFactorDecoratorRotation.h"
#include "IMaterial.h"

#include <boost/scoped_ptr.hpp>

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
            const IRotation &rotation);

    virtual Particle *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual Particle *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial& material);

    //! Returns particle's material.
    virtual const IMaterial* getAmbientMaterial() const;

    //! Create a form factor for this particle with an extra scattering factor
    virtual IFormFactor *createTransformedFormFactor(complex_t wavevector_scattering_factor,
                                                     const IRotation* p_rotation,
                                                     kvector_t translation) const;

    //! Sets _material_.
    virtual void setMaterial(const IMaterial& material);

    //! Returns particle's material.
    virtual const IMaterial* getMaterial() const;

    //! Returns refractive index of the particle
    virtual complex_t getRefractiveIndex() const;

    //! Sets the form factor
    void setFormFactor(const IFormFactor& form_factor);

    //! Returns the form factor
    const IFormFactor* getFormFactor() const;

protected:
    boost::scoped_ptr<IMaterial> mP_material;
    boost::scoped_ptr<IMaterial> mP_ambient_material;
    boost::scoped_ptr<IFormFactor> mP_form_factor;
private:
    void initialize();
};

#endif // PARTICLE_H


