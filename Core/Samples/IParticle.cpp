// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/IParticle.cpp
//! @brief     Implements generic member functions of IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorPositionFactor.h"
#include "IParticle.h"

using namespace BornAgain;

IFormFactor* IParticle::createFormFactor() const
{
    return createTransformedFormFactor(nullptr, kvector_t());
}

void IParticle::setRotation(const IRotation &rotation)
{
    if (!mP_rotation.get()) {
        mP_rotation.reset(rotation.clone());
        registerChild(mP_rotation.get());
        return;
    }
    deregisterChild(mP_rotation.get());
    mP_rotation.reset(rotation.clone());
    registerChild(mP_rotation.get());
}

void IParticle::applyRotation(const IRotation &rotation)
{
    if (mP_rotation.get()) {
        deregisterChild(mP_rotation.get());
        mP_rotation.reset(CreateProduct(rotation, *mP_rotation));
    } else {
        mP_rotation.reset(rotation.clone());
    }
    m_position = rotation.getTransform3D().transformed(m_position);
    registerChild(mP_rotation.get());
}

void IParticle::applyTranslation(kvector_t displacement)
{
    m_position += displacement;
}

IRotation* IParticle::createComposedRotation(const IRotation* p_rotation) const
{
    if (p_rotation) {
        if (mP_rotation.get()) {
            return CreateProduct(*p_rotation, *mP_rotation);
        } else {
            return p_rotation->clone();
        }
    } else {
        if (mP_rotation.get()) {
            return mP_rotation->clone();
        } else {
            return 0;
        }
    }
}

kvector_t IParticle::getComposedTranslation(
    const IRotation* p_rotation, kvector_t translation) const
{
    if (p_rotation) {
        Geometry::Transform3D transform = p_rotation->getTransform3D();
        return translation + transform.transformed(m_position);
    } else {
        return translation + m_position;
    }
}

void IParticle::registerPosition()
{
    registerParameter(PositionX, &m_position[0]);
    registerParameter(PositionY, &m_position[1]);
    registerParameter(PositionZ, &m_position[2]);
}
