// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/IParticle.cpp
//! @brief     Implements generic member functions of IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IParticle.h"
#include "IFormFactor.h"
#include "FormFactorDecoratorRotation.h"
#include "FormFactorDecoratorPositionFactor.h"

void IParticle::setRotation(const IRotation &rotation)
{
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
    applyTransformationToSubParticles(rotation);
}

IFormFactor *IParticle::createTransformedFormFactor(const IFormFactor &bare_ff) const
{
    IFormFactor *p_bare_clone = bare_ff.clone();
    IFormFactor *p_intermediate;
    if (mP_rotation.get()) {
        p_intermediate = new FormFactorDecoratorRotation(p_bare_clone, *mP_rotation);
    } else {
        p_intermediate = p_bare_clone;
    }
    IFormFactor *p_result;
    if (m_position != kvector_t()) {
        p_result = new FormFactorDecoratorPositionFactor(*p_intermediate, m_position);
        delete p_intermediate;
    } else {
        p_result = p_intermediate;
    }
    return p_result;
}
