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

    //! Sets particle position, including depth.
    void setPosition(kvector_t position);

    //! Returns rotation object
    const IRotation *getRotation() const
    {
        return mP_rotation.get();
    }

    //! Sets transformation.
    void setRotation(const IRotation &rotation);

    //! Applies transformation by composing it with the existing one
    void applyRotation(const IRotation &rotation);

protected:
    virtual void applyTransformationToSubParticles(const IRotation &rotation) = 0;
    IFormFactor *createTransformedFormFactor(const IFormFactor &bare_ff) const;
    kvector_t m_position;
    boost::scoped_ptr<IRotation> mP_rotation;
    bool m_has_transformation_info;
};

inline void IParticle::setPosition(kvector_t position)
{
    if (!m_has_transformation_info) {
        throw RuntimeErrorException("IParticle::setPosition: "
                                    "can only be called for IParticle objects that "
                                    "contain transformation information");
    }
    m_position = position;
}

inline void IParticle::setRotation(const IRotation &rotation)
{
    if (!m_has_transformation_info) {
        throw RuntimeErrorException("IParticle::setRotation: "
                                    "can only be called for IParticle objects that "
                                    "contain transformation information");
    }
    if (!mP_rotation.get()) {
        mP_rotation.reset(rotation.clone());
        registerChild(mP_rotation.get());
        applyTransformationToSubParticles(rotation);
        return;
    }
    deregisterChild(mP_rotation.get());
    boost::scoped_ptr<IRotation> P_inverse_rotation(mP_rotation->createInverse());
    applyTransformationToSubParticles(*P_inverse_rotation);
    mP_rotation.reset(rotation.clone());
    registerChild(mP_rotation.get());
    applyTransformationToSubParticles(rotation);
}

inline void IParticle::applyRotation(const IRotation &rotation)
{
    if (mP_rotation.get()) {
        deregisterChild(mP_rotation.get());
        mP_rotation.reset(CreateProduct(rotation, *mP_rotation));
    } else {
        mP_rotation.reset(rotation.clone());
    }
    registerChild(mP_rotation.get());
    applyTransformationToSubParticles(rotation);
}

#endif // IPARTICLE_H
