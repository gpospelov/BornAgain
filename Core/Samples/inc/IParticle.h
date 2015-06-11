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

#include <boost/scoped_ptr.hpp>

//! @class IParticle
//! @ingroup samples
//! @brief Interface for a generic particle

class BA_CORE_API_ IParticle : public ICompositeSample
{
public:
    virtual ~IParticle()
    {
    }
    virtual IParticle *clone() const = 0;

    //! Returns a clone with inverted magnetic fields
    virtual IParticle *cloneInvertB() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const
    {
        visitor->visit(this);
    }

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial &material)
    {
        (void)material;
    }

    //! Returns particle's material.
    virtual const IMaterial *getAmbientMaterial() const = 0;

    //! Create a form factor which includes the particle's shape,
    //! material, ambient material, an optional transformation and an extra
    //! scattering factor
    virtual IFormFactor *createFormFactor(complex_t wavevector_scattering_factor) const=0;

    //! Returns particle position, including depth.
    kvector_t getPosition() const
    {
        return m_position;
    }

    //! Returns depth of particle
    double getDepth() const
    {
        return -m_position.z();
    }

    //! Sets particle position, including depth.
    void setPosition(kvector_t position)
    {
        m_position = position;
    }

    //! Returns rotation object
    const IRotation *getRotation() const
    {
        return mP_rotation.get();
    }

    //! Sets transformation.
    void setRotation(const IRotation &rotation);

    //! Applies transformation by composing it with the existing one
    void applyRotation(const IRotation &rotation);

    //! Applies extra translation by adding it to the current one
    void applyTranslation(kvector_t displacement);

protected:
    //! Creates a form factor decorated with the IParticle's position/rotation
    IFormFactor *createTransformedFormFactor(const IFormFactor &bare_ff) const;

    virtual void applyTransformationToSubParticles(const IRotation &rotation) = 0;
    kvector_t m_position;
    boost::scoped_ptr<IRotation> mP_rotation;
};

#endif // IPARTICLE_H
