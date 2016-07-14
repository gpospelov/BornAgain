// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/IParticle.h
//! @brief     Declares interface IParticle.
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

#include <memory>
#include "ICompositeSample.h"
#include "IMaterial.h"

//! @class IAbstractParticle
//! @ingroup samples
//! @brief Interface for a generic particle

class BA_CORE_API_ IAbstractParticle : public ICompositeSample
{
public:
    IAbstractParticle() : m_abundance(1.0) {}
    virtual ~IAbstractParticle() {}
    virtual IAbstractParticle *clone() const = 0;

    //! Returns a clone with inverted magnetic fields
    virtual IAbstractParticle *cloneInvertB() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! Sets the refractive index of the ambient material (which influences its
    //! scattering power)
    virtual void setAmbientMaterial(const IMaterial &material);

    //! Returns abundance.
    double getAbundance() const;

    //! Sets abundance.
    void setAbundance(double abundance);

    //! Returns particle's material.
    virtual const IMaterial *getAmbientMaterial() const = 0;

protected:
    double m_abundance;
};

//! @class IParticle
//! @ingroup samples
//! @brief Interface for a real particle (one that has position/rotation and form factor)

class BA_CORE_API_ IParticle : public IAbstractParticle
{
public:
    virtual ~IParticle() {}
    virtual IParticle *clone() const = 0;

    //! Returns a clone with inverted magnetic fields
    virtual IParticle *cloneInvertB() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const;

    //! Create a form factor for this particle
    IFormFactor *createFormFactor() const;

    //! Create a form factor for this particle with an extra scattering factor
    virtual IFormFactor *createTransformedFormFactor(const IRotation *p_rotation,
                                                     kvector_t translation) const = 0;

    //! Returns particle position.
    kvector_t getPosition() const;

    //! Sets particle position.
    void setPosition(kvector_t position);

    //! Sets particle position.
    void setPosition(double x, double y, double z);

    //! Returns rotation object
    const IRotation *getRotation() const;

    //! Sets transformation.
    void setRotation(const IRotation &rotation);

    //! Applies transformation by composing it with the existing one
    void applyRotation(const IRotation &rotation);

    //! Applies extra translation by adding it to the current one
    void applyTranslation(kvector_t displacement);

protected:
    //! Creates a composed IRotation object
    IRotation *createComposedRotation(const IRotation *p_rotation) const;

    //! Gets a composed translation vector
    kvector_t getComposedTranslation(const IRotation *p_rotation, kvector_t translation) const;

    //! Registers the three components of its position
    void registerPosition();

    kvector_t m_position;
    std::unique_ptr<IRotation> mP_rotation;
};

inline void IAbstractParticle::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

inline void IAbstractParticle::setAmbientMaterial(const IMaterial& /*material*/)
{
}

inline double IAbstractParticle::getAbundance() const
{
    return m_abundance;
}

inline void IAbstractParticle::setAbundance(double abundance)
{
    m_abundance = abundance;
}

inline void IParticle::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

inline kvector_t IParticle::getPosition() const
{
    return m_position;
}

inline void IParticle::setPosition(kvector_t position)
{
    m_position = position;
}

inline void IParticle::setPosition(double x, double y, double z)
{
    m_position = kvector_t(x, y, z);
}

inline const IRotation *IParticle::getRotation() const
{
    return mP_rotation.get();
}

#endif // IPARTICLE_H
